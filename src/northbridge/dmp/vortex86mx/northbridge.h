#ifndef NORTHBRIDGE_DMP_VORTEX86MX_H
#define NORTHBRIDGE_DMP_VORTEX86MX_H

#define	NB			PCI_DEV(0, 0, 0)
#define	NB_REG_VID		0x00
#define	NB_REG_DID		0x02
#define	NB_REG_CMD		0x04
#define	NB_REG_STS		0x06
#define	NB_REG_RID		0x08
#define	NB_REG_CLS_CODE		0x09
#define	NB_REG_HAD_TYPE		0x0E
#define	NB_REG_SUB_VID		0x2C
#define	NB_REG_SUB_DID		0x2E
#define	NB_REG_SPI_BASE		0x40
#define	NB_REG_BUF_SC		0x44
#define	NB_REG_NBOCDCR		0x4A
#define	NB_REG_GPUUMACR		0x4B
#define	NB_REG_STRAP		0x60
#define	NB_REG_MCPS		0x66
#define	NB_REG_SDRAM_MTR	0x68
#define	NB_REG_SDRAM_MCR	0x6A
#define	NB_REG_MBR		0x6C
#define	NB_REG_MRR		0x6E
#define	NB_REG_IO_CCR		0x70
#define	NB_REG_CPU_DCR		0x72
#define	NB_REG_DDR_MTR		0x74
#define	NB_REG_SMM		0x83
#define	NB_REG_MAR		0x84
#define	NB_REG_CID		0x90
#define	NB_REG_S1R		0x94
#define	NB_REG_S2R		0x98
#define	NB_REG_S3R		0x9C
#define	NB_REG_HOST_CTL		0xA0
#define	NB_REG_CPU_MBCR		0xC4
#define	NB_REG_CDR		0xD0
#define	NB_REG_PACR		0xF0
#define	NB_REG_PMCR		0xF4
#define	NB_REG_PCI_TARGET	0xF8
#define	NB_REG_PCSCR		0xFC

/* Additional "virtual" device, just extension of NB */
#define NB1			PCI_DEV(0, 0, 1)
#define NB1_REG_DDRII_PHY_CTL3	0x50
#define NB1_REG_DDR_PWR_SAV	0xBC
#define NB1_REG_DDRII_CTL_OPT1	0xC0
#define NB1_REG_DDRII_CTL_OPT2	0xC4
#define NB1_REG_DDRII_CTL_OPT3	0xC8
#define NB1_REG_DDRII_CTL_OPT4	0xCC
#define NB1_REG_TEST_MODE	0xD0
#define NB1_REG_PCI_DELAY_LINE	0xD1
#define NB1_REG_L2_CACHE_CTL	0xE8
#define NB1_REG_SSCR		0xEC
#define NB1_REG_DDRII_CTL	0xF0

unsigned int vortex86mx_scan_root_bus(device_t root, unsigned int max);
extern void (*realmode_interrupt)(u32 intno, u32 eax, u32 ebx, u32 ecx, u32 edx, 
		u32 esi, u32 edi) __attribute__((regparm(0)));

#endif /* NORTHBRIDGE_DMP_VORTEX86MX_H */
