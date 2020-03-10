# Coding Style

## Naming

* Class names: Class (as well as types and structs) should be Pascal Case (examples: `MyType`, `Animal`, `CodeHero`)
* Variables: Variables should be camelCase (examples: `myType`, `thisIsAnotherVar`)
* Members: Should be prefixed by `m_` and `m_p` for pointers.
* Function arguments: Should be camelCase too prefixed by `i` for input only, `o` for outputOnly, `io` for input-output (example: iFirstName, oThisIsAnArgUsedToOutput, ioUsedForBoth)
* FunctionAndMethod: Should be PascalCased (examples: CodeHero::StartAndRun())