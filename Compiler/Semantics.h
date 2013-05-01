/* Semantics.h
   The action and supporting routines for performing semantics processing.
*/

#ifndef Semantics_H_
#define Semantics_H_

/* Semantic Records */
typedef struct IdList {
  struct SymEntry * TheEntry;
  struct IdList * Next;
} IdList;

typedef struct ExprRes {
  int Reg;
  struct InstrSeq * Instrs;
} ExprRes;

typedef struct ExprResList {
	struct ExprRes *Expr;
	struct ExprResList * Next;
} ExprResList;

typedef struct BExprRes {
  char * Label;
  struct InstrSeq * Instrs;
} BExprRes;


/* Semantics Actions */
extern struct ExprRes *  doIntLit(char * digits);
extern struct ExprRes *  doRval(char * name);
extern struct InstrSeq *  doAssign(char * name,  struct ExprRes * Res1);
extern struct ExprRes *  doAdd(struct ExprRes * Res1,  struct ExprRes * Res2);
ExprRes * doSubtr(ExprRes * Res1, ExprRes * Res2);
ExprRes * doDiv(ExprRes * Res1, ExprRes * Res2);
ExprRes * doMod(ExprRes * Res1, ExprRes * Res2);
extern struct ExprRes *  doMult(struct ExprRes * Res1,  struct ExprRes * Res2);
extern struct InstrSeq *  doPrint(struct ExprRes * Expr);
extern struct BExprRes * doBExpr (struct ExprRes * Res1,  struct ExprRes * Res2);
extern struct InstrSeq * doIf(struct BExprRes *bRes, struct InstrSeq * seq);

extern void	Finish(struct InstrSeq *Code);

#endif /* Semantics_H_ */
