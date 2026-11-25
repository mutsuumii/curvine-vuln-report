# Missing NULL check after allocation
# CWE-476 | Severity: HIGH
# File: crates/adapters/curvine-storage-spdk/csrc/spdk_opts_helper.c line 94

**Risk:** Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
