import WASILibc

@_extern(wasm, module: "wasi_snapshot_preview1", name: "sock_open")
@_extern(c)
func sock_open_v2(addressFamily: Int32, socketType: UInt32, fileDescriptor: UnsafeMutablePointer<Int32>?) -> Int

@_extern(wasm, module: "wasi_snapshot_preview1", name: "sock_bind")
@_extern(c)
func sock_bind_v2(fileDescriptor: Int32, addressPointer: UnsafeRawPointer?, port: UInt32) -> Int

@_extern(wasm, module: "wasi_snapshot_preview1", name: "sock_listen")
@_extern(c)
func sock_listen_v2(fileDescriptor: Int32, backlog: Int32) -> Int

@_extern(wasm, module: "wasi_snapshot_preview1", name: "sock_accept")
@_extern(c)
func sock_accept_v2(fileDescriptor: Int32, connection: UnsafeMutablePointer<Int32>?) -> Int

@main
struct WasmEdge {
  enum Error: Swift.Error {
    case socketError(Int)
    case bindError(Int)
    case listenError(Int)
    case acceptError(Int)
    case readError(Int)
  }

  static func main() throws {
    var fileDescriptor: Int32 = 0
    var error = sock_open_v2(addressFamily: AF_INET, socketType: 2, fileDescriptor: &fileDescriptor)

    guard error == 0 else {
      perror("webserver (socket)")
      throw Error.socketError(error)
    }

    print("socket created successfully")

    var hostAddress = UInt32(INADDR_ANY).bigEndian

    error = withUnsafeBytes(of: &hostAddress) {
      var address = ($0.baseAddress, $0.count)
      
      return withUnsafeBytes(of: &address) {
        sock_bind_v2(fileDescriptor: fileDescriptor, addressPointer: $0.baseAddress, port: UInt32(8080))
      }
    }

    guard error == 0 else {
      perror("webserver (bind)")
      throw Error.bindError(error)
    }
    print("socket successfully bound to address");

    error = sock_listen_v2(fileDescriptor: fileDescriptor, backlog: 128)
    guard error == 0 else {
      perror("webserver (listen)")
      throw Error.listenError(error)
    }
    print("server listening for connections");

    repeat {
      var connection: Int32 = 0
      error = sock_accept_v2(fileDescriptor: fileDescriptor, connection: &connection)

      guard error == 0 else {
        perror("webserver (accept)")
        throw Error.acceptError(error)
      }
      print("accepted new connection");

      var buffer = [UInt8](repeating: 0, count: 1024)
      _ = buffer.withContiguousMutableStorageIfAvailable {
        read(connection, $0.baseAddress, $0.count)
      }

      print(String(decoding: buffer, as: UTF8.self))

      var response = "HTTP/1.1 204 No Content\r\n"
      _ = response.withUTF8 {
        write(connection, $0.baseAddress, $0.count)
      }

      close(connection)
    } while true
  }
}
