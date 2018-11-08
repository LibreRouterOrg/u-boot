#!/usr/bin/env bash
#set -x

USAGE="Usage: $0 path/to/openwrt-sdk (something like openwrt-sdk-18.06.1-ar71xx-generic_gcc-7.3.0_musl.Linux-x86_64/staging_dir/toolchain-mips_24kc_gcc-7.3.0_musl/bin)"

if ! [[ -d "$1" ]]; then
    echo "No argument supplied or invalid path"
    echo $USAGE
    exit 1
fi

export PATH=$PATH:$1
export CROSS_COMPILE=mips-openwrt-linux-musl-
export ATH_CFG_SGMII=1
export ATH_CONFIG_SWAP_SGMII=0
export ATH_GMAC0_MII=ATHR_RGMII
export ATH_GMAC1_MII=ATHR_SGMII
export ATH_GMAC_GE0_IS_CONNECTED=1
export ATH_GMAC_GE1_IS_CONNECTED=1
export ATH_RGMII_CAL=1
export ATH_S17_MAC0_SGMII=1
export ATH_S17_PHY0_WAN=1
export ATH_SGMII_FORCED=1
export BIG_ENDIAN_HOST=1
export BUILD_TYPE=jffs2
export BUS=dual
export CFG_BOARD_TYPE=LibreRouter-1.0
export COMPRESSED_UBOOT=0
export ETH_CONFIG=_s17
export FLASH_SIZE=16

# clean
make distclean

# configure
make LibreRouter-1.0_config

# build
STAGING_DIR= LC_ALL=C make V=1
