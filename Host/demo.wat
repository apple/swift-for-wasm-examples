(module
  (import "host" "print"
          (func $print (param (; pointer ;) i32 (; offset ;) i32)))
  (export "main" (func $main))

  (memory 1)

  (func $factorial (param $arg i64) (result i64)
    local.get $arg
    i64.eqz
    if (result i64)
      then
      i64.const 1

      else
        local.get $arg
        i64.const 1
        i64.sub
        local.get $arg
        call $factorial
        i64.mul
)

  (func $main (result i64)
    (call $factorial (i64.const 10))
    (call $print (i32.const 0) (i32.const 13))
  )

  (data (i32.const 0) "Hello, World!")
)
