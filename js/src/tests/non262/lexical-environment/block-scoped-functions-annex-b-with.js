// Global functions are configurable in a browser environment.
var functionDeclarationsConfigurable = typeof document !== "undefined";

var o = { f: "string-f" };
with (o) {
  var desc = Object.getOwnPropertyDescriptor(this, "f");
  assertEq(desc.value, undefined);
  assertEq(desc.writable, true);
  assertEq(desc.enumerable, true);
  assertEq(desc.configurable, functionDeclarationsConfigurable);
  function f() {
    return "fun-f";
  }
}

// Annex B explicitly assigns to the nearest VariableEnvironment, so the
// with-object "o" should have its property unchanged.
assertEq(o.f, "string-f");
assertEq(f(), "fun-f");

reportCompare(true, true)
