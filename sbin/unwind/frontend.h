/*	$OpenBSD: frontend.h,v 1.4 2019/11/11 05:51:06 florian Exp $	*/

/*
 * Copyright (c) 2018 Florian Obser <florian@openbsd.org>
 * Copyright (c) 2004, 2005 Esben Norby <norby@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

TAILQ_HEAD(ctl_conns, ctl_conn)	ctl_conns;

struct trust_anchor {
	TAILQ_ENTRY(trust_anchor)	 entry;
	char				*ta;
};

TAILQ_HEAD(trust_anchor_head, trust_anchor);

struct imsg_rdns_proposal {
	uint32_t		 if_index;
	struct sockaddr_rtdns	 rtdns;
};

void		 frontend(int, int);
void		 frontend_dispatch_main(int, short, void *);
void		 frontend_dispatch_resolver(int, short, void *);
void		 frontend_dispatch_captiveportal(int, short, void *);
int		 frontend_imsg_compose_main(int, pid_t, void *, uint16_t);
int		 frontend_imsg_compose_resolver(int, pid_t, void *, uint16_t);
int		 frontend_imsg_compose_captiveportal(int, pid_t, void *, uint16_t);
char		*ip_port(struct sockaddr *);
void		 add_new_ta(struct trust_anchor_head *, char *);
void		 free_tas(struct trust_anchor_head *);
int		 merge_tas(struct trust_anchor_head *,
		    struct trust_anchor_head *);
