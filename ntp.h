#ifndef __NTP_H
#define __NTP_H

#define JAN_1970    2208988800UL        /* 1970 - 1900 in seconds */
#define NTP_SERVER_NAME "42.121.121.79"    //my windows 7 ntp server
#define NTP_PORT    123
/* some ntp server
time-a.nist.gov
time-b.nist.gov
time-a.timefreq.bldrdoc.gov
time-b.timefreq.bldrdoc.gov
time-c.timefreq.bldrdoc.gov
utcnist.colorado.edu
ntp.tuxfamily.net
time-nw.nist.gov
nist1.datum.com
nist1-ny.glassey.com
nist1.aol-ca.truetime.com
ntp2.belbone.be
ntp.doubleukay.com
ntp0.cs.mu.OZ.AU
time.apple.com
0.pool.ntp.org
1.pool.ntp.org
2.pool.ntp.org
2.europe.pool.ntp.org
3.europe.pool.ntp.org
1.north-america.pool.ntp.org
2.north-america.pool.ntp.org
0.oceania.pool.ntp.org
1.oceania.pool.ntp.org
0.au.pool.ntp.org
3.au.pool.ntp.org
*/

typedef struct  
{
	unsigned char LiVnMode;
	unsigned char Stratum;
	unsigned char Poll;
	unsigned char Precision;
	long int RootDelay;
	long int RootDispersion;
	char RefID[4];
	long int RefTimeInt;
	long int RefTimeFraction;
	long int OriTimeInt;
	long int OriTimeFraction;
	long int RecvTimeInt;
	long int RecvTimeFraction;
	long int TranTimeInt;
	long int TranTimeFraction;
}STNP_Header;

int SYNC_Time(void);

#endif
