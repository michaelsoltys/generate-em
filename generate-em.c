// Calculates bits of Ehrenfeucht-Mycielski sequence
// by Grzegorz Herman and Michael Soltys
// December 2007
//
// Usage:
//	generate <n>
// with <n> being the requested number of bits.
// Warning: uses 57 Bytes of RAM per generated bit

#include "malloc.h"

// structures used
struct branch
{
	char*		l;
	char*		r;
	struct node*	n;
};
struct node
{
	char*		p;
	struct branch	b[2];
};

// data pointers
char*		dhead;
char*		dtail;
// node pointers
struct node*	nhead;
struct node*	ntail;

// creates a new node
struct node* newnode(char* p)
{
	struct node* n;
	n = ++ntail;
	n->p = p;
	return n;
}

// updates branch information
void setbranch(struct node* u, char b, char* l, char* r, struct node* n)
{
	u->b[b].l = l;
	u->b[b].r = r;
	u->b[b].n = n;
}

// calculates the matching bit
char nextb(char bit)
{
	char *f, *i, *j, *k, *l;
	char ci, cj, ck;
	struct node *u, *v, *w;
	*(++dtail) = bit;
	f = i = dtail;
	u = nhead;
	while (1)
	{
		f = u->p + 1;
		u->p = dtail;
		k = i;
		ck = *k & 1;
		w = u->b[ck].n;
		if (w == NULL)
			break;
		l = u->b[ck].l;
		j = u->b[ck].r;
		while (j > l)
		{
			ci = *i & 1;
			cj = *j & 1;
			if (ci != cj)
			{
				// split existing branch
				f = w->p + 1;
				v = newnode(dtail);
				setbranch(v, cj, l, j, w);
				setbranch(v, ci, dhead, i, newnode(dtail));
				setbranch(u, ck, i, k, v);
				return *f;
			}
			i--, j--;
		}
		// follow existing branch
		v = u->b[ck].n;
		setbranch(u, ck, i, k, v);
		u = v;
	}
	// add new branch
	ci = *i & 1;
	setbranch(u, ci, dhead, i, newnode(dtail));
	return *f;
}

int main(int argc, char* argv[])
{
	int n;
	char* c;
	n = 0;
	for (c = argv[1]; *c; ++c)
		n = 10*n + *c - '0';
	// initialize
	dhead = dtail = (char*) malloc((n+2)*sizeof(char));
	nhead = ntail = (struct node*) malloc(2*n*sizeof(struct node));
	nhead->p = dhead;
	// build
	char b = '0';
	while (dtail < dhead+n)
		b = ('0'+'1') - nextb(b);
	// output
	*(++dtail) = '\n';
	write(1, dhead+1, dtail-dhead);
	return 0;
}
