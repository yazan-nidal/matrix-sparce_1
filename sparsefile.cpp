#include "iostream"
#include <string>
using namespace std;

typedef int itemtype;

struct nodetype
{ itemtype value;
  int col, row;
  struct nodetype *nextcol, *nextrow;
};

typedef struct nodetype *nodepointer;

nodepointer findAbove(int column, nodepointer m)
{ nodepointer c, r;
  for(c = m; c->col != column; c = c->nextcol);
  for(r = c; r->nextrow != c; r = r->nextrow);
  return r;
}

void insertafter(nodepointer m, nodepointer &co, int column, itemtype i)
{	nodepointer p, q;	     
	p = new nodetype;
    p->row = co->row;  p->value = i;
    p->nextcol = co->nextcol;
    co->nextcol = p;
    co = p;
	q = findAbove(column, m);
	p->col = q->col;
	p->nextrow = q->nextrow;
	q->nextrow = p;
}

/*
itemtype remove (nodepointer &head)
{   nodepointer  q;
    itemtype i;
	if (head.first != NULL)
    {    q = head.first;     
        head.first  = q->next;  
        i = q->value;
	    free(q);
		return i;
     }
    else cout << "List is empty";
}

*/

void print(nodepointer head, int n)
{   
	cout << "The matrix is" << endl;
	for (nodepointer r = head->nextrow; r != head ; r = r->nextrow)
	  { int column = 1;
		for (nodepointer c = r->nextcol;  column <=n ; column++)
			if(column == c->col )
			   { 
				 cout << c->value <<" ";
		         c = c->nextcol;
		       }
			else cout << 0 <<" ";
	    cout << endl;
	  }
}

nodepointer InitilaizeMatrix(int n)
{ nodepointer p, q, r;
  r = new nodetype;
  r->col = r->row = r->value = 0;
  r->nextrow = r->nextcol = r;
  q = r;
  for (int i=1; i<=n; i++)
  { // create the header row for the columns
	  p = new nodetype;
	  p->col = i;
	  p->row = p->value = 0;
      p->nextrow = p;
	  p->nextcol = r;
	  q->nextcol = p;
	  q = p;
  }

  q = r;
  for (int i=1; i<=n; i++)
  { // create the header column for the rows
	  p = new nodetype;
	  p->row = i;
	  p->col = p->value = 0;
      p->nextcol = p;
	  p->nextrow = r;
	  q->nextrow = p;
	  q = p;
  }


  return r;
}


nodepointer ReadMatrix(int n)
{ nodepointer p, q, c, r, mtx;
  int val;
  mtx = InitilaizeMatrix(n);
  r = mtx->nextrow;
  for(int i = 1; i<= n; i++)
  {   c = r;
	  cout << "Enter the values in row #" << i<<endl;
	  for (int j = 1; j <= n; j++)
	  { 
		  cin >> val;
		  if (val)
			  insertafter(mtx, c, j, val); //insert a node with value val in the matrix mtx after the node c in the J th column 
	  }
	  r = r ->nextrow;
  }
  return mtx;
}


nodepointer add(nodepointer m1, nodepointer m2, int n)
{ nodepointer p1, p2, q1, q2, r, c;
  nodepointer m3;
  m3 = InitilaizeMatrix(n);
  for(  r = m3->nextrow, p1 = m1->nextrow, p2 = m2->nextrow ; (p1 != m1) && (p2 != m2); p1 = p1->nextrow, p2 = p2->nextrow)
	 {for( c = r->nextcol, q1 = p1->nextcol, q2 = p2->nextcol ; (q1 != p1) && (q2 != p2) ;)
         { if (q1->col == q2->col)
			{  insertafter(m3, c, q1->col, q1->value + q2->value);
			   q1 = q1->nextcol; q2 = q2->nextcol;
			}
		  else if (q1->col < q2->col)
			{  insertafter(m3, c, q1->col, q1->value);
			   q1 = q1->nextcol;
			}
		 else
		   {   insertafter(m3, c, q2->col, q2->value);
			   q2 = q2->nextcol;
			}
        }
	  for( ; q1 != p1 ; )
			{  insertafter(m3, c, q1->col, q1->value);
			   q1 = q1->nextcol;
			}
	  for( ; q2 != p2 ; )
            {  insertafter(m3, c, q2->col, q2->value);
			   q2 = q2->nextcol;
			}
       r = r->nextrow;
  }
  return m3; 
}



void main()
{ nodepointer MTX1, MTX2, MTX3;
  int n;
  cout << "Enter number number of rows/coulmns ===> ";
    cin >> n;
  cout << "Enter the matrix "<<endl;
  MTX1 = ReadMatrix(n);
  cout << "The Entered matrix "<<endl;
  print(MTX1, n);

  cout << "Enter the matrix "<<endl;
  MTX2 = ReadMatrix(n);
  cout << "The Entered matrix "<<endl;
  print(MTX2, n); 
  cout << "The Sum of the two matrices "<<endl;
  MTX3 = add(MTX1, MTX2, n);
  print(MTX3, n);
}
