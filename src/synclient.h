/* 
 * File:   synclient.h
 * Author: spencer
 *
 * Created on January 25, 2011, 10:15 AM
 */

#ifndef SYNCLIENT_H
#define	SYNCLIENT_H

#include <xorg/synaptics.h>

int is_equal(SynapticsSHM *s1, SynapticsSHM *s2);
SynapticsSHM* shm_init(void);
int initsynclient(int *xmin, int *xmax, int *ymin, int *ymax, int *zmin, int *zmax);

#endif	/* SYNCLIENT_H */

