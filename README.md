# Security audit: CurvineIO/curvine

Date: 2026-11-25 | Auditor: [mutsuumii](https://github.com/mutsuumii)

## Summary

Found 12 issue(s): 12 high.

## Findings

### 1. [HIGH] Path traversal via unsanitized input

**CWE-22** | `scripts/perf/test_disk_speed_standalone_v2.py` line 90

File path built from user input. Attacker reads/writes arbitrary files using ../ sequences.

```
img_list = [os.path.join(args.img_dir, img) for img in img_list]
```

**Fix:** Use os.path.realpath() and verify result starts with the expected base directory.
---

### 2. [HIGH] Integer overflow in size calculation

**CWE-190** | `crates/adapters/curvine-ufs-oss-hdfs/ffi/jindosdk_ffi.cpp` line 400

Arithmetic in allocator argument can overflow to a small value, causing under-allocation and subsequent heap overflow.

```
out->file_infos = (JindoFileInfo*)malloc(sizeof(JindoFileInfo) * count);
```

**Fix:** Validate sizes before arithmetic. Use calloc(n, size) for n*size. Check: if (n > SIZE_MAX / size) abort().
---

### 3. [HIGH] Use-after-free pattern

**CWE-416** | `crates/adapters/curvine-ufs-oss-hdfs/ffi/jindosdk_ffi.cpp` line 402

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(out);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 4. [HIGH] Use-after-free pattern

**CWE-416** | `crates/adapters/curvine-ufs-oss-hdfs/ffi/jindosdk_ffi.cpp` line 418

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(out);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 5. [HIGH] Use-after-free pattern

**CWE-416** | `crates/adapters/curvine-ufs-oss-hdfs/ffi/jindosdk_ffi.cpp` line 1531

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
if (p) free(p);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 6. [HIGH] Missing NULL check after allocation

**CWE-476** | `crates/adapters/curvine-ufs-oss-hdfs/ffi/jindosdk_ffi.cpp` line 355

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
auto* out = (JindoFileInfo*)malloc(sizeof(JindoFileInfo));
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 7. [HIGH] Missing NULL check after allocation

**CWE-476** | `crates/adapters/curvine-ufs-oss-hdfs/ffi/jindosdk_ffi.cpp` line 385

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
auto* out = (JindoListResult*)malloc(sizeof(JindoListResult));
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 8. [HIGH] Missing NULL check after allocation

**CWE-476** | `crates/adapters/curvine-ufs-oss-hdfs/ffi/jindosdk_ffi.cpp` line 400

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
out->file_infos = (JindoFileInfo*)malloc(sizeof(JindoFileInfo) * count);
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 9. [HIGH] Path traversal via unsanitized input

**CWE-22** | `scripts/perf/test_disk_speed_standalone.py` line 87

File path built from user input. Attacker reads/writes arbitrary files using ../ sequences.

```
img_list = [os.path.join(args.img_dir, img) for img in img_list]
```

**Fix:** Use os.path.realpath() and verify result starts with the expected base directory.
---

### 10. [HIGH] Path traversal via unsanitized input

**CWE-22** | `curvine-libsdk/python/test/curvineFileSystemTest.py` line 66

File path built from user input. Attacker reads/writes arbitrary files using ../ sequences.

```
reader = fs.open(test_path+"/a.txt")
```

**Fix:** Use os.path.realpath() and verify result starts with the expected base directory.
---

### 11. [HIGH] Use-after-free pattern

**CWE-416** | `crates/adapters/curvine-storage-spdk/csrc/spdk_opts_helper.c` line 97

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
spdk_dma_free(buf);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 12. [HIGH] Missing NULL check after allocation

**CWE-476** | `crates/adapters/curvine-storage-spdk/csrc/spdk_opts_helper.c` line 94

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
return spdk_dma_zmalloc(size, align, NULL);
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---
