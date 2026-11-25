# Path traversal via unsanitized input
# CWE-22 | Severity: HIGH
# File: scripts/perf/test_disk_speed_standalone.py line 87

**Risk:** File path built from user input. Attacker reads/writes arbitrary files using ../ sequences.

**Fix:** Use os.path.realpath() and verify result starts with the expected base directory.
