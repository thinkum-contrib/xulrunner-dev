// |jit-test| allow-unhandlable-oom; skip-if: !('oomTest' in this)

try {
    gcparam("maxBytes", gcparam("gcBytes"));
    newGlobal("");
} catch (e) {};
oomTest(function() {})
