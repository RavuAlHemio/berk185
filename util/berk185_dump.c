/*
 * Copyright (c) 1990, 1993, 1994, 1995, 1996, 1997, 1998
 *	Sleepycat Software.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Redistributions in any form must be accompanied by information on
 *    how to obtain complete source code for the DB software and any
 *    accompanying software that uses the DB software.  The source code
 *    must either be included in the distribution or be available for no
 *    more than the cost of distribution plus a nominal fee, and must be
 *    freely redistributable under reasonable conditions.  For an
 *    executable file, complete source code means the source code for all
 *    modules it contains.  It does not mean source code for modules or
 *    files that typically accompany the operating system on which the
 *    executable file runs, e.g., standard library modules or system
 *    header files.
 *
 * THIS SOFTWARE IS PROVIDED BY SLEEPYCAT SOFTWARE ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL SLEEPYCAT SOFTWARE BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
/*
 * Copyright (c) 1990, 1993, 1994, 1995
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
/*
 * Copyright (c) 1995, 1996
 *	The President and Fellows of Harvard University.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by Harvard University
 *	and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY HARVARD AND ITS CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL HARVARD OR ITS CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static const char copyright[] =
"@(#) Copyright (c) 1996, 1997, 1998\n\
	Sleepycat Software Inc.  All rights reserved.\n";
static const char sccsid[] = "@(#)db_dump185.c	10.10 (Sleepycat) 4/10/98";
#endif

#ifndef NO_SYSTEM_INCLUDES
#include <sys/types.h>

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#endif

#include <berk185.h>

/* Hash Table Information */
typedef struct hashhdr185 {		/* Disk resident portion */
	int		magic;		/* Magic NO for hash tables */
	int		version;	/* Version ID */
	u_int32_t	lorder;		/* Byte Order */
	int		bsize;		/* Bucket/Page Size */
	int		bshift;		/* Bucket shift */
	int		dsize;		/* Directory Size */
	int		ssize;		/* Segment Size */
	int		sshift;		/* Segment shift */
	int		ovfl_point;	/* Where overflow pages are being
					 * allocated */
	int		last_freed;	/* Last overflow page freed */
	int		max_bucket;	/* ID of Maximum bucket in use */
	int		high_mask;	/* Mask to modulo into entire table */
	int		low_mask;	/* Mask to modulo into lower half of
					 * table */
	int		ffactor;	/* Fill factor */
	int		nkeys;		/* Number of keys in hash table */
} HASHHDR185;
typedef struct htab185	 {		/* Memory resident data structure */
	HASHHDR185 	hdr;		/* Header */
} HTAB185;

/* Hash Table Information */
typedef struct hashhdr186 {	/* Disk resident portion */
	int32_t	magic;		/* Magic NO for hash tables */
	int32_t	version;	/* Version ID */
	int32_t	lorder;		/* Byte Order */
	int32_t	bsize;		/* Bucket/Page Size */
	int32_t	bshift;		/* Bucket shift */
	int32_t	ovfl_point;	/* Where overflow pages are being allocated */
	int32_t	last_freed;	/* Last overflow page freed */
	int32_t	max_bucket;	/* ID of Maximum bucket in use */
	int32_t	high_mask;	/* Mask to modulo into entire table */
	int32_t	low_mask;	/* Mask to modulo into lower half of table */
	int32_t	ffactor;	/* Fill factor */
	int32_t	nkeys;		/* Number of keys in hash table */
	int32_t	hdrpages;	/* Size of table header */
	int32_t	h_charkey;	/* value of hash(CHARKEY) */
#define NCACHED	32		/* number of bit maps and spare points */
	int32_t	spares[NCACHED];/* spare pages for overflow */
	u_int16_t	bitmaps[NCACHED];	/* address of overflow page bitmaps */
} HASHHDR186;
typedef struct htab186	 {		/* Memory resident data structure */
	HASHHDR186 	hdr;		/* Header */
} HTAB186;

typedef struct _epgno {
	u_int32_t pgno;			/* the page number */
	u_int16_t index;		/* the index on the page */
} EPGNO;

typedef struct _epg {
	void	*page;			/* the (pinned) page */
	u_int16_t index;		/* the index on the page */
} EPG;

typedef struct _cursor {
	EPGNO	 pg;			/* B: Saved tree reference. */
	DBT	 key;			/* B: Saved key, or key.data == NULL. */
	u_int32_t rcursor;		/* R: recno cursor (1-based) */

#define	CURS_ACQUIRE	0x01		/*  B: Cursor needs to be reacquired. */
#define	CURS_AFTER	0x02		/*  B: Unreturned cursor after key. */
#define	CURS_BEFORE	0x04		/*  B: Unreturned cursor before key. */
#define	CURS_INIT	0x08		/* RB: Cursor initialized. */
	u_int8_t flags;
} CURSOR;

/* The in-memory btree/recno data structure. */
typedef struct _btree {
	void	 *bt_mp;		/* memory pool cookie */

	void	 *bt_dbp;		/* pointer to enclosing DB */

	EPG	  bt_cur;		/* current (pinned) page */
	void	 *bt_pinned;		/* page pinned across calls */

	CURSOR	  bt_cursor;		/* cursor */

	EPGNO	  bt_stack[50];		/* stack of parent pages */
	EPGNO	 *bt_sp;		/* current stack pointer */

	DBT	  bt_rkey;		/* returned key */
	DBT	  bt_rdata;		/* returned data */

	int	  bt_fd;		/* tree file descriptor */

	u_int32_t bt_free;		/* next free page */
	u_int32_t bt_psize;		/* page size */
	u_int16_t bt_ovflsize;		/* cut-off for key/data overflow */
	int	  bt_lorder;		/* byte order */
					/* sorted order */
	enum { NOT, BACK, FORWARD } bt_order;
	EPGNO	  bt_last;		/* last insert */

					/* B: key comparison function */
	int	(*bt_cmp) __P((const DBT *, const DBT *));
					/* B: prefix comparison function */
	size_t	(*bt_pfx) __P((const DBT *, const DBT *));
					/* R: recno input function */
	int	(*bt_irec) __P((struct _btree *, u_int32_t));

	FILE	 *bt_rfp;		/* R: record FILE pointer */
	int	  bt_rfd;		/* R: record file descriptor */

	void	 *bt_cmap;		/* R: current point in mapped space */
	void	 *bt_smap;		/* R: start of mapped space */
	void	 *bt_emap;		/* R: end of mapped space */
	size_t	  bt_msize;		/* R: size of mapped region. */

	u_int32_t bt_nrecs;		/* R: number of records */
	size_t	  bt_reclen;		/* R: fixed record length */
	u_char	  bt_bval;		/* R: delimiting byte/pad character */

/*
 * NB:
 * B_NODUPS and R_RECNO are stored on disk, and may not be changed.
 */
#define	B_INMEM		0x00001		/* in-memory tree */
#define	B_METADIRTY	0x00002		/* need to write metadata */
#define	B_MODIFIED	0x00004		/* tree modified */
#define	B_NEEDSWAP	0x00008		/* if byte order requires swapping */
#define	B_RDONLY	0x00010		/* read-only tree */

#define	B_NODUPS	0x00020		/* no duplicate keys permitted */
#define	R_RECNO		0x00080		/* record oriented tree */

#define	R_CLOSEFP	0x00040		/* opened a file pointer */
#define	R_EOF		0x00100		/* end of input file reached. */
#define	R_FIXLEN	0x00200		/* fixed length records */
#define	R_MEMMAPPED	0x00400		/* memory mapped file. */
#define	R_INMEM		0x00800		/* in-memory file */
#define	R_MODIFIED	0x01000		/* modified file */
#define	R_RDONLY	0x02000		/* read-only file */

#define	B_DB_LOCK	0x04000		/* DB_LOCK specified. */
#define	B_DB_SHMEM	0x08000		/* DB_SHMEM specified. */
#define	B_DB_TXN	0x10000		/* DB_TXN specified. */
	u_int32_t flags;
} BTREE;

void	db_btree __P((DB *, int));
void	db_hash __P((DB *, int));
void	dbt_dump __P((DBT *));
void	dbt_print __P((DBT *));
int	main __P((int, char *[]));
void	usage __P((void));

const char
	*progname = "berk185_dump";			/* Program name. */


static void
berk_verr(int eval, const char *fmt, va_list ap)
{
	(void)fprintf(stderr, "%s: ", progname);
	if (fmt != NULL) {
		(void)vfprintf(stderr, fmt, ap);
		(void)fputs(": ", stderr);
		(void)fputs(strerror(errno), stderr);
	}
	(void)fputs("\n", stderr);
	exit(eval);
}

static void
berk_err(int eval, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	berk_verr(eval, fmt, ap);
	va_end(ap);
}

int
main(argc, argv)
	int argc;
	char *argv[];
{
	extern char *optarg;
	extern int optind;
	DB *dbp;
	DBT key, data;
	int ch, pflag, rval;

	pflag = 0;
	while ((ch = getopt(argc, argv, "f:p")) != EOF)
		switch (ch) {
		case 'f':
			if (freopen(optarg, "w", stdout) == NULL)
				berk_err(1, "%s", optarg);
			break;
		case 'p':
			pflag = 1;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc != 1)
		usage();

	if ((dbp = dbopen(argv[0], O_RDONLY, 0, DB_BTREE, NULL)) == NULL) {
		if ((dbp = dbopen(argv[0], O_RDONLY, 0, DB_HASH, NULL)) == NULL)
			berk_err(1, "%s", argv[0]);
		db_hash(dbp, pflag);
	} else
		db_btree(dbp, pflag);

	/*
	 * !!!
	 * DB 1.85 DBTs are a subset of DB 2.0 DBTs, so we just use the
	 * new dump/print routines.
	 */
	if (pflag)
		while (!(rval = dbp->seq(dbp, &key, &data, R_NEXT))) {
			dbt_print(&key);
			dbt_print(&data);
		}
	else
		while (!(rval = dbp->seq(dbp, &key, &data, R_NEXT))) {
			dbt_dump(&key);
			dbt_dump(&data);
		}

	if (rval == -1)
		berk_err(1, "seq");
	return (0);
}

/*
 * db_hash --
 *	Dump out hash header information.
 */
void
db_hash(dbp, pflag)
	DB *dbp;
	int pflag;
{
	HTAB185 *hash185p;
	HTAB186 *hash186p;

	printf("format=%s\n", pflag ? "print" : "bytevalue");
	printf("type=hash\n");

	/* DB 1.85 was version 2, DB 1.86 was version 3. */
	hash185p = dbp->internal;
	if (hash185p->hdr.version > 2) {
		hash186p = dbp->internal;
		printf("h_ffactor=%lu\n", (u_long)hash186p->hdr.ffactor);
		if (hash186p->hdr.lorder != 0)
			printf("db_lorder=%lu\n", (u_long)hash186p->hdr.lorder);
		printf("db_pagesize=%lu\n", (u_long)hash186p->hdr.bsize);
	} else {
		printf("h_ffactor=%lu\n", (u_long)hash185p->hdr.ffactor);
		if (hash185p->hdr.lorder != 0)
			printf("db_lorder=%lu\n", (u_long)hash185p->hdr.lorder);
		printf("db_pagesize=%lu\n", (u_long)hash185p->hdr.bsize);
	}
	printf("HEADER=END\n");
}

/*
 * db_btree --
 *	Dump out btree header information.
 */
void
db_btree(dbp, pflag)
	DB *dbp;
	int pflag;
{
	BTREE *btp;

	btp = dbp->internal;

	printf("format=%s\n", pflag ? "print" : "bytevalue");
	printf("type=btree\n");
#ifdef NOT_AVAILABLE_IN_185
	printf("bt_minkey=%lu\n", (u_long)XXX);
	printf("bt_maxkey=%lu\n", (u_long)XXX);
#endif
	if (btp->bt_lorder != 0)
		printf("db_lorder=%lu\n", (u_long)btp->bt_lorder);
	printf("db_pagesize=%lu\n", (u_long)btp->bt_psize);
	if (!(btp->flags & B_NODUPS))
		printf("duplicates=1\n");
	printf("HEADER=END\n");
}

static char hex[] = "0123456789abcdef";

/*
 * dbt_dump --
 *	Write out a key or data item using byte values.
 */
void
dbt_dump(dbtp)
	DBT *dbtp;
{
	size_t len;
	u_int8_t *p;

	for (len = dbtp->size, p = dbtp->data; len--; ++p)
		(void)printf("%c%c",
		    hex[(*p & 0xf0) >> 4], hex[*p & 0x0f]);
	printf("\n");
}

/*
 * dbt_print --
 *	Write out a key or data item using printable characters.
 */
void
dbt_print(dbtp)
	DBT *dbtp;
{
	size_t len;
	u_int8_t *p;

	for (len = dbtp->size, p = dbtp->data; len--; ++p)
		if (isprint(*p)) {
			if (*p == '\\')
				(void)printf("\\");
			(void)printf("%c", *p);
		} else
			(void)printf("\\%c%c",
			    hex[(*p & 0xf0) >> 4], hex[*p & 0x0f]);
	printf("\n");
}

/*
 * usage --
 *	Display the usage message.
 */
void
usage()
{
	(void)fprintf(stderr, "usage: %s [-p] [-f file] db_file\n", progname);
	exit(1);
}
