/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef _AG7240_PHY_H
#define _AG7240_PHY_H

#ifdef CFG_ATHRS26_PHY
extern int athrs26_phy_setup(int ethUnit);
extern int athrs26_phy_is_up(int ethUnit);
extern int athrs26_phy_is_fdx(int ethUnit);
extern int athrs26_phy_speed(int ethUnit);
#endif

static inline void ag7240_phy_setup(int unit)
{
#ifdef CONFIG_AR7242_S16_PHY
    if ((is_ar7242() || is_wasp()) && (unit==0)) {
        athrs16_phy_setup(unit);
    } else
#endif
    {
        athrs26_phy_setup(unit);
#ifdef CONFIG_F1E_PHY
        athr_phy_setup(unit);
#endif
    }
}

static inline void ag7240_phy_link(int unit, int *link)
{
#ifdef CONFIG_AR7242_S16_PHY
    if ((is_ar7242() || is_wasp()) && (unit==0)) {
         *link = athrs16_phy_is_up(unit);
    } else
#endif
    {
#ifdef CFG_ATHRS27_PHY
         *link = athrs27_phy_is_up(unit);
#endif
#ifdef CFG_ATHRS26_PHY
         *link = athrs26_phy_is_up(unit);
#endif
#ifdef CONFIG_F1E_PHY
         *link = athr_phy_is_up(unit);
#endif
    }
}

static inline void ag7240_phy_duplex(int unit, int *duplex)
{
#ifdef CONFIG_AR7242_S16_PHY
    if ((is_ar7242() || is_wasp()) && (unit==0)) {
        *duplex = athrs16_phy_is_fdx(unit);
    } else
#endif
    {
        *duplex = athrs26_phy_is_fdx(unit);
#ifdef CONFIG_F1E_PHY
        *duplex = athr_phy_is_fdx(unit);
#endif
    }
}

static inline void ag7240_phy_speed(int unit, int *speed)
{
#ifdef CONFIG_AR7242_S16_PHY
    if ((is_ar7242() || is_wasp()) && (unit==0)) {
        *speed = athrs16_phy_speed(unit);
    } else
#endif
    {
        *speed = athrs26_phy_speed(unit);
#ifdef CONFIG_F1E_PHY
        *speed = athr_phy_speed(unit);
#endif
    }
}

#endif /*_AG7240_PHY_H*/
