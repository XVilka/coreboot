#ifndef NORTHBRIDGE_DMP_VORTEX86MX_H
#define NORTHBRIDGE_DMP_VORTEX86MX_H

unsigned int vortex86mx_scan_root_bus(device_t root, unsigned int max);
extern void (*realmode_interrupt)(u32 intno, u32 eax, u32 ebx, u32 ecx, u32 edx, 
		u32 esi, u32 edi) __attribute__((regparm(0)));

#endif /* NORTHBRIDGE_DMP_VORTEX86MX_H */
