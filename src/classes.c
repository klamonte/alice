






#include "alice.h"
#include "action.h"
#include "token.h"
#include "typecodes.h"
#include "class.h"
static ActionNum cROOT[] =  {
	TOK_PROG, EXPAND + N_PROGRAM,	/* cant normally happen */
	TOK_PROCEDURE, EXPAND+N_DECL_PROC,
	TOK_FUNCTION, EXPAND+N_DECL_FUNC,
	0 } ;

static NodeNum nROOT[] = {N_PROGRAM, N_DECL_PROC, N_DECL_FUNC, 0} ;
static ActionNum cCOMMENT[] =  {
	TOK_CMNT, ACT_CONTOK,
	0 } ;

static NodeNum nCOMMENT[] = { N_T_COMMENT, 0 } ;
static ActionNum cINIT[] =  {
	TOK_INT, ACT_CONTOK,
	TOK_ID, ACT_RECID,
	TOK_NUMB, ACT_CONTOK,
	TOK_CHAR, ACT_CONTOK,
	TOK_STRING, ACT_CONTOK,
	TOK_PLUS, ACT_CONTOK,
	TOK_MINUS, ACT_CONTOK,
	TOK_LPAREN, EXPAND+N_INIT_STRUCT,
	TOK_COLON, EXPAND+N_FLD_INIT,
	TOK_LBRACKET, EXPAND+N_EXP_SET,
	0 } ;
static type_code tINIT[] = { T_CONST, T_BCONST, T_BENUM, T_ENUM_ELEMENT, T_UNDEF, T_FIELD, 0 };
static NodeNum nINIT[] = { N_ID, N_CON_INT, N_CON_CHAR, N_CON_STRING, N_CON_REAL,
		N_CON_PLUS, N_CON_MINUS, N_INIT_STRUCT, N_FLD_INIT,
		N_EXP_SET, 0 };
static ActionNum cLABEL[] =  {
	TOK_INT, EXPAND + N_ID,
	0 } ;
static type_code tLABEL[] = { T_LABEL, 0 };
static NodeNum nLABEL[] = { N_ID, 0 }
	;
static ActionNum cPROC_ID[] = {
	TOK_ID, EXPAND + N_ID,
	0 } ;
static type_code tPROC_ID[] = { T_PROCEDURE, T_BPROC, T_READLN, T_WRITELN, T_BTPROC, T_LPROC,
		T_FORM_PROCEDURE, T_UNDEF, 0 };
static NodeNum nPROC_ID[] = { N_ID, 0 }
	;
static ActionNum cFUN_ID[] =  {
	TOK_ID, EXPAND + N_ID,
	0 } ;
static type_code tFUN_ID[] = { T_FUNCTION, T_BFUNC, T_LFUNC, T_BTFUNC, T_FORM_FUNCTION, T_UNDEF, 0 };
static NodeNum nFUN_ID[] = { N_ID, 0 }
	;
static ActionNum cPROGRAM[] =  { 
	TOK_PROG, ACT_DPGM,
	0 } ;

static NodeNum nPROGRAM[] = { N_PROGRAM, 0 } ;
static ActionNum cDECLARATIONS[] =  {
	TOK_FOR, EXPAND + N_FORWARD,
	TOK_CR, ACT_IGNORE,
	TOK_CMNT, ACT_COMMENT,
	TOK_NOT, EXPAND + N_NOTDONE,
	0 } ;

static NodeNum nDECLARATIONS[] = { N_DECL_VAR, N_DECL_TYPE, N_DECL_CONST, N_DECL_LABEL, N_DECL_PROC,
		N_HIDE, N_REVEAL, N_LIBRARY,
		N_DECL_FUNC, N_FORWARD, N_ST_COMMENT, N_NOTDONE, 0 } ;
static ActionNum cLABEL_DECL[] =  {
	TOK_INT, ACT_DECLARE,
	0 } ;

static NodeNum nLABEL_DECL[] = {N_DECL_ID, 0 } ;
static ActionNum cCONST_DECL[] =  {
	TOK_ID, ACT_CDID,
	TOK_EQ, EXPAND + N_CONST_DECL,
	TOK_COLON, EXPAND + N_CONST_INIT,
	TOK_CMNT, ACT_COMMENT,
	TOK_NOT, EXPAND + N_NOTDONE,
	TOK_CR, ACT_IGNORE,
	0 } ;

static NodeNum nCONST_DECL[] = { N_CONST_INIT, N_CONST_DECL, N_HIDE, N_REVEAL, N_ST_COMMENT,
		N_NOTDONE, 0 } ;
static ActionNum cTYPE_DECL[] =  {
	TOK_ID, ACT_TDID,
	TOK_EQ, EXPAND + N_TYPE_DECL,
	TOK_CR, ACT_IGNORE,
	TOK_CMNT, ACT_COMMENT,
	TOK_NOT, EXPAND + N_NOTDONE,
	0 } ;

static NodeNum nTYPE_DECL[] = { N_TYPE_DECL, N_HIDE, N_REVEAL, N_ST_COMMENT, N_NOTDONE, 0 } ;
static ActionNum cVAR_DECL[] =  {
	TOK_ID, ACT_VDID,
	TOK_COLON, EXPAND + N_VAR_DECL,
	TOK_ABSOLUTE, EXPAND + N_VAR_ABSOLUTE,
	TOK_CR, ACT_IGNORE,
	TOK_CMNT, ACT_COMMENT,
	TOK_NOT, EXPAND + N_NOTDONE,
	0 } ;

static NodeNum nVAR_DECL[] = { N_VAR_DECL, N_VAR_ABSOLUTE, N_HIDE, N_REVEAL, N_ST_COMMENT,
				N_NOTDONE, 0 } ;
static ActionNum cCONSTANT[] =  {
	TOK_INT, ACT_CONTOK,
	TOK_ID, ACT_CONTOK,
	TOK_NUMB, ACT_CONTOK,
	TOK_CHAR, ACT_CONTOK,
	TOK_STRING, ACT_CONTOK,
	TOK_PLUS, ACT_CONTOK,
	TOK_MINUS, ACT_CONTOK,
	0 } ;
static type_code tCONSTANT[] = { T_CONST, T_BCONST, T_BENUM, T_ENUM_ELEMENT, T_UNDEF, 0 };
static NodeNum nCONSTANT[] = { N_ID, N_CON_INT, N_CON_CHAR, N_CON_STRING, N_CON_REAL,
		N_CON_PLUS, N_CON_MINUS, 0 };
static ActionNum cTYPE[] =  {
	TOK_ID, ACT_TYPID,
	/* TOK_ID will actually be smarter */
	TOK_ARRAY, EXPAND + N_TYP_ARRAY,
#ifdef TURBO
	TOK_STTYPE, EXPAND + N_TYP_STRING,
#endif
	TOK_SET, EXPAND + N_TYP_SET,
	TOK_FILE, EXPAND + N_TYP_FILE,
	TOK_UPARROW, EXPAND + N_TYP_POINTER,
	TOK_RECORD, ACT_RECORD,
	TOK_LPAREN, EXPAND + N_TYP_ENUM,
	TOK_MINUS, ACT_TYPSR,
	TOK_CHAR, ACT_TYPSR,	/* single chars only */
	TOK_INT, ACT_TYPSR,
	TOK_PACKED, EXPAND + N_TYP_PACKED,
	0 } ;
static type_code tTYPE[] = { T_TYPE, T_BTYPE, T_BBTYPE, T_UNDEF, 0 };
static NodeNum nTYPE[] = { N_TYP_ARRAY, N_ID, N_TYP_SET, N_TYP_FILE, N_TYP_POINTER,
#ifdef TURBO
		N_TYP_STRING,
#endif
		N_TYP_RECORD, N_TYP_ENUM, N_TYP_SUBRANGE, N_TYP_PACKED, 0 }
	;
static ActionNum cTYPEID[] = {
	TOK_ID, ACT_TYPID,
	0} ;
static type_code tTYPEID[] = { T_TYPE, T_BTYPE, T_BBTYPE, T_UNDEF, 0 };
static NodeNum nTYPEID[] = { N_ID, 0 }
	;
static ActionNum cSIM_TYPE[] = {
	TOK_ID, ACT_TYPID,
	TOK_LPAREN, EXPAND + N_TYP_ENUM,
	TOK_DOTDOT, EXPAND + N_TYP_SUBRANGE,
	TOK_DOT, EXPAND+N_TYP_SUBRANGE,
	TOK_PLUS, ACT_TYPSR,
	TOK_MINUS, ACT_TYPSR,
	TOK_CHAR, ACT_TYPSR,	/* single chars only */
	TOK_INT, ACT_TYPSR,
	0} ;
static type_code tSIM_TYPE[] = { T_TYPE, T_BTYPE, T_BBTYPE, T_UNDEF, 0 };
static NodeNum nSIM_TYPE[] = { N_ID, N_TYP_ENUM, N_TYP_SUBRANGE, 0 }
	;
static ActionNum cST_TYPE[] = {
	TOK_ARRAY, EXPAND + N_TYP_ARRAY,
	TOK_SET, EXPAND + N_TYP_SET,
	TOK_FILE, EXPAND + N_TYP_FILE,
	TOK_RECORD, ACT_RECORD,
	0} ;

static NodeNum nST_TYPE[] = { N_TYP_ARRAY, N_TYP_SET, N_TYP_FILE, N_TYP_RECORD, 0 } ;
static ActionNum cFIELD[] =  {
	TOK_ID, ACT_FDID,
	TOK_CR, ACT_IGNORE,
	TOK_CASE, EXPAND+N_VARIANT,
	TOK_COLON, EXPAND+N_FIELD,
	TOK_CMNT, ACT_COMMENT,
	TOK_NOT, EXPAND + N_NOTDONE,
	0 } ;

static NodeNum nFIELD[] = { N_FIELD, N_HIDE, N_REVEAL, N_VARIANT, N_ST_COMMENT, N_NOTDONE,  0 }
	;
static ActionNum cFORMAL[] =  {
	TOK_VAR, EXPAND + N_FORM_REF,
	TOK_SEMI, ACT_EXPLIST,
	TOK_PROCEDURE, ACT_DPPROC,
	TOK_FUNCTION, ACT_DPFUNC,
	TOK_ID, ACT_PDID,
	0 } ;

static NodeNum nFORMAL[] = {N_FORM_REF, N_FORM_VALUE, N_FORM_FUNCTION, N_FORM_PROCEDURE, 0 } ;
static ActionNum cSTATEMENT[] =  {
	TOK_ASSIGN, EXPAND + N_ST_ASSIGN,
	TOK_IF, EXPAND + N_ST_IF,
	TOK_CMNT, ACT_COMMENT,
	TOK_WHILE, EXPAND + N_ST_WHILE,
	TOK_FOR, EXPAND + N_ST_FOR,
	TOK_CASE, EXPAND + N_ST_CASE,
	TOK_DOWNTO, EXPAND + N_ST_DOWNTO,
	TOK_REPEAT, EXPAND + N_ST_REPEAT,
	TOK_LPAREN, EXPAND + N_ST_CALL,
	TOK_GOTO, EXPAND + N_ST_GOTO,
	/* Actually should have routine here to resolve situation */
	TOK_ID, ACT_STID,
	TOK_QUESTION, ACT_WRITELN,
	TOK_WITH, EXPAND + N_ST_WITH,
	TOK_BEGIN, EXPAND + N_ST_BLOCK,
	TOK_INT, ACT_LBSTAT,
	TOK_COLON, EXPAND + N_ST_ASSIGN,
	TOK_EQ, EXPAND + N_ST_ASSIGN,
	TOK_CR, ACT_IGNORE,
	TOK_DO, EXPAND + N_ST_TRACE,
	TOK_NOT, EXPAND + N_NOTDONE,
	0 } ;
static type_code tSTATEMENT[] = {T_VAR,T_INIT, T_FILENAME,T_PROCEDURE, T_BPROC, T_BTPROC, T_READLN, T_WRITELN,  T_LPROC,
		T_FIELD, T_FORM_REF, T_FORM_VALUE, T_FORM_PROCEDURE, T_ABSVAR,
		T_FUNCTION, 0};
static NodeNum nSTATEMENT[] = { N_ST_ASSIGN, N_ST_IF, N_ST_ELSE, N_ST_COMMENT, N_NOTDONE,
		N_ST_WHILE, N_ST_FOR, N_HIDE, N_REVEAL,
		N_ST_CASE, N_ST_DOWNTO, N_ST_REPEAT, N_ST_CALL, N_ST_GOTO,
		N_ST_WITH, N_ST_BLOCK, N_ST_LABEL, 0 }
	;
static ActionNum cCASE[] =  {
	/* These cases should expand another production */
	TOK_ID, ACT_CCONST,
	TOK_INT, ACT_CCONST,
	TOK_ELSE, EXPAND + N_CASE_ELSE,
	TOK_CHAR, ACT_CCONST,
	TOK_PLUS, ACT_CCONST,
	TOK_MINUS, ACT_CCONST,
	TOK_COMMA, ACT_EXPLIST,
	TOK_CMNT, ACT_COMMENT,
	TOK_NOT, EXPAND+N_NOTDONE,
	TOK_CR, ACT_IGNORE,
	0 } ;

static NodeNum nCASE[] = {N_CASE, N_HIDE, N_REVEAL, N_CASE_ELSE, N_ST_COMMENT, N_NOTDONE, 0 } ;
static ActionNum cVAR[] =  {
	TOK_ID, EXPAND + N_ID,
	TOK_LBRACKET, EXPAND + N_VAR_ARRAY,
	TOK_DOT, EXPAND + N_VAR_FIELD,
	TOK_UPARROW, EXPAND + N_VAR_POINTER,
	0 } ;
static type_code tVAR[] = { T_VAR, T_FORM_REF, T_FORM_VALUE,T_FILENAME, T_UNDEF,
		T_MEMVAR, T_PORTVAR, T_ABSVAR, T_INIT, T_FIELD, 0 };
static NodeNum nVAR[] = { N_ID, N_VAR_ARRAY, N_VAR_FIELD, N_VAR_POINTER, N_VF_WITH, 0 }
	;
static ActionNum cEXP[] =  {
	/* Special provisions should be made for "type in expression" mode */
	TOK_RBRACKET, EXPAND + N_VAR_ARRAY,
	TOK_RPAREN, EXPAND + N_EXP_FUNC,
	TOK_LPAREN, EXPAND + N_EXP_PAREN,
	TOK_PLUS, EXPAND + N_EXP_PLUS,		/* ambiguous */
	TOK_MINUS, EXPAND + N_EXP_MINUS,	/* ambiguous */
	TOK_STAR, EXPAND + N_EXP_TIMES,
	TOK_SLASH, EXPAND + N_EXP_SLASH,
	TOK_DIV, EXPAND + N_EXP_DIV,
	TOK_MOD, EXPAND + N_EXP_MOD,
	TOK_EQ, EXPAND + N_EXP_EQ,
	TOK_NE, EXPAND + N_EXP_NE,
	TOK_LT, EXPAND + N_EXP_LT,
	TOK_LE, EXPAND + N_EXP_LE,
	TOK_GT, EXPAND + N_EXP_GT,
	TOK_GE, EXPAND + N_EXP_GE,
	TOK_NOT, EXPAND + N_EXP_NOT,
	TOK_AND, EXPAND + N_EXP_AND,
	TOK_OR, EXPAND + N_EXP_OR,
#ifdef TURBO
	TOK_XOR, EXPAND + N_EXP_XOR,
	TOK_SHL, EXPAND + N_EXP_SHL,
	TOK_SHR, EXPAND + N_EXP_SHR,
#endif
	TOK_IN, EXPAND + N_EXP_IN,
	TOK_PLUS, EXPAND + N_EXP_UPLUS,
	TOK_MINUS, EXPAND + N_EXP_UMINUS,
	TOK_LBRACKET, EXPAND + N_EXP_SET,	/* ambiguous */
	TOK_NIL, EXPAND + N_EXP_NIL,
	TOK_DOT, EXPAND + N_VAR_FIELD,
	TOK_DOTDOT, ACT_SET_SUBRANGE,
/* Because of assignment statements, we cannot allow colon to be a prefix
 * operator for expressions, since "david <space> := " would create
 * david := <value> = <value> : <value>
 */
/*	TOK_COLON, EXPAND + N_OEXP_2,   ... Remove prefix colons on exps */
	TOK_UPARROW, EXPAND + N_VAR_POINTER,

	TOK_ID, ACT_EXPID,
	TOK_INT, ACT_CONTOK,
	TOK_NUMB, ACT_CONTOK,
	TOK_CHAR, ACT_CONTOK,
	TOK_STRING, ACT_CONTOK,

	0 } ;
static type_code tEXP[] = { T_VAR, T_CONST, T_BCONST, T_BENUM, T_ENUM_ELEMENT, T_FORM_VALUE, T_FORM_REF,
		T_ABSVAR, T_INIT, T_FUNCTION, T_BFUNC, T_BTFUNC, T_FORM_FUNCTION, T_LFUNC,
		T_FIELD, T_FILENAME, T_PROCEDURE, T_FORM_PROCEDURE, T_UNDEF,0};
static NodeNum nEXP[] = { N_VAR_ARRAY, N_EXP_FUNC, N_EXP_PAREN, N_EXP_PLUS, N_EXP_MINUS,
	 N_EXP_TIMES, N_EXP_SLASH, N_EXP_DIV, N_EXP_MOD, N_EXP_EQ,
	 N_EXP_NE, N_EXP_LT, N_EXP_LE, N_EXP_GT, N_EXP_GE, N_EXP_NOT,
	 N_EXP_AND, N_EXP_OR, N_EXP_IN, N_EXP_UPLUS, N_EXP_UMINUS,
	 N_OEXP_3, N_OEXP_2,
	 N_EXP_SET, N_EXP_NIL, N_SET_SUBRANGE,
	 N_VAR_FIELD, N_VAR_POINTER, N_VF_WITH, N_ID,
#ifdef TURBO
	 N_EXP_XOR, N_EXP_SHL, N_EXP_SHR,
#endif
	 N_CON_INT, N_CON_REAL, N_CON_STRING, N_CON_CHAR, 0 }
	;
static ActionNum cCASECONST[] =  {
	TOK_INT, ACT_CONTOK,
	TOK_ID, ACT_CONTOK,
	TOK_CHAR, ACT_CONTOK,
	TOK_PLUS, ACT_CONTOK,
	TOK_MINUS, ACT_CONTOK,
	TOK_DOTDOT, EXPAND+N_TYP_SUBRANGE,
	TOK_DOT, EXPAND+N_TYP_SUBRANGE,
	0 } ;
static type_code tCASECONST[] = { T_CONST, T_BCONST, T_BENUM, T_ENUM_ELEMENT, T_UNDEF, 0 };
static NodeNum nCASECONST[] = { N_CON_CHAR, N_CON_INT, N_ID, N_CON_PLUS, N_TYP_SUBRANGE,
		N_CON_MINUS, 0 };
static ActionNum cDECL_ID[] =  {
	TOK_ID, ACT_DECLARE,
	0 } ;

static NodeNum nDECL_ID[] = {N_DECL_ID, 0 } ;
static ActionNum cHIDECL_ID[] =  {
	TOK_ID, ACT_HDECLARE,
	0 } ;

static NodeNum nHIDECL_ID[] = {N_DECL_ID, 0 } ;
static ActionNum cBLCOMMENT[] =  {
	TOK_CMNT, ACT_COMMENT,
	TOK_CR, ACT_IGNORE,
	0 } ;

static NodeNum nBLCOMMENT[] = {N_ST_COMMENT, N_HIDE, N_REVEAL, 0 } ;
static ActionNum cVARIANT[] =  {
	TOK_COLON, EXPAND+N_ST_VCASE,
	TOK_LPAREN, EXPAND+N_ST_VCASE,
	TOK_ID, ACT_CCONST,
	TOK_INT, ACT_CCONST,
	TOK_CHAR, ACT_CCONST,
	TOK_PLUS, ACT_CCONST,
	TOK_MINUS, ACT_CCONST,
	TOK_CMNT, ACT_COMMENT,
	TOK_NOT, EXPAND+N_NOTDONE,
	TOK_CR, ACT_IGNORE,
	0 } ;

static NodeNum nVARIANT[] = { N_ST_VCASE, N_ST_COMMENT, N_NOTDONE,  0 } ;
static ActionNum cFLD_NAME[] =  {
	TOK_ID, ACT_FDUSE,
	0} ;
static type_code tFLD_NAME[] = { T_FIELD, 0 };
static NodeNum nFLD_NAME[] = { N_ID, 0 };
static ActionNum cPASSUP[] = {
	0} ;

static NodeNum nPASSUP[] = { 0 } ;
static ActionNum cOCONSTANT[] =  {
	TOK_INT, ACT_CONTOK,
	TOK_ID, ACT_CONTOK,
	TOK_CHAR, ACT_CONTOK,
	TOK_PLUS, ACT_CONTOK,
	TOK_MINUS, ACT_CONTOK,
	0 } ;
static type_code tOCONSTANT[] = { T_CONST, T_BCONST, T_BENUM, T_ENUM_ELEMENT, T_UNDEF, 0 };
static NodeNum nOCONSTANT[] = { N_CON_CHAR, N_CON_INT, N_ID, N_CON_PLUS, N_CON_MINUS, 0 };
static ActionNum cPNAME[] =  {
	TOK_ID, ACT_IDCOMMENT,
	0 } ;

static NodeNum nPNAME[] = { N_T_COMMENT, 0 } ;
static ActionNum cSPECIAL[] = {
	TOK_IF, ACT_BLCHG,
	TOK_WHILE, ACT_BLCHG,
	TOK_REPEAT, ACT_BLCHG,
	TOK_FOR, ACT_BLCHG,
	TOK_CMNT, ACT_COMCHG,
	TOK_BEGIN, ACT_BLCHG,
	0 };

static NodeNum nSPECIAL[] = { 0 } ;
static ActionNum cROUTNAME[] = {
	TOK_ID, EXPAND + N_ID,
	0 } ;
static type_code tROUTNAME[] = { T_PROCEDURE, T_FUNCTION, T_UNDEF, 0 };
static NodeNum nROUTNAME[] = { N_ID, 0 }
	;
static ActionNum cABSID[] = {
#ifndef LARGEPTR
	TOK_ID, EXPAND+N_ID,
#else
	TOK_ID, ACT_ABSCON,
	TOK_COLON, EXPAND+N_OEXP_2,
	TOK_INT, ACT_ABSCON,
	TOK_CHAR, ACT_ABSCON,
	TOK_PLUS, ACT_ABSCON,
	TOK_MINUS, ACT_ABSCON,
#endif
	0 } ;
static type_code tABSID[] = { T_VAR, T_FORM_VALUE, T_FORM_REF,
		T_ABSVAR, T_INIT, T_FILENAME, T_UNDEF,0};
static NodeNum nABSID[] = { N_ID, N_OEXP_2, 0 }
	;
 ActionNum *Class_Actions[] = {
cROOT,
cCOMMENT,
cINIT,
cLABEL,
cPROC_ID,
cFUN_ID,
cPROGRAM,
cDECLARATIONS,
cLABEL_DECL,
cCONST_DECL,
cTYPE_DECL,
cVAR_DECL,
cCONSTANT,
cTYPE,
cTYPEID,
cSIM_TYPE,
cST_TYPE,
cFIELD,
cFORMAL,
cSTATEMENT,
cCASE,
0,
cVAR,
cEXP,
cCASECONST,
cDECL_ID,
cHIDECL_ID,
cBLCOMMENT,
cVARIANT,
cFLD_NAME,
cPASSUP,
cOCONSTANT,
cPNAME,
cSPECIAL,
cROUTNAME,
cABSID,
 0};
 char *Class_Names[] = {
"Code-Root",
"Comment",
"initializer",
"Label Number",
"Procedure Name",
"Function Name",
"Pascal Program",
"Declarations",
"Label",
"Constant Declaration",
"Type Declaration",
"Variable Declaration",
"Constant",
"Type",
"Type-Name",
"Simple-Type",
"Structured-Type",
"Field-Declaration",
"Parameter",
"Statement",
"Case-Instance",
0,
"Variable",
"Value",
"Case Constant",
"Name",
"Routine Name",
"{Comment that says what the routine does}",
"Variant",
"Field",
"Anything",
"Constant",
"Ignored Name",
"Block-Statement",
"Routine-Name",
"Absolute Address",
 0};
 type_code *Class_Types[] = {
0,
0,
tINIT,
tLABEL,
tPROC_ID,
tFUN_ID,
0,
0,
0,
0,
0,
0,
tCONSTANT,
tTYPE,
tTYPEID,
tSIM_TYPE,
0,
0,
0,
tSTATEMENT,
0,
0,
tVAR,
tEXP,
tCASECONST,
0,
0,
0,
0,
tFLD_NAME,
0,
tOCONSTANT,
0,
0,
tROUTNAME,
tABSID,
 0};
 NodeNum *Valid_Nodes[] = {
nROOT,
nCOMMENT,
nINIT,
nLABEL,
nPROC_ID,
nFUN_ID,
nPROGRAM,
nDECLARATIONS,
nLABEL_DECL,
nCONST_DECL,
nTYPE_DECL,
nVAR_DECL,
nCONSTANT,
nTYPE,
nTYPEID,
nSIM_TYPE,
nST_TYPE,
nFIELD,
nFORMAL,
nSTATEMENT,
nCASE,
0,
nVAR,
nEXP,
nCASECONST,
nDECL_ID,
nHIDECL_ID,
nBLCOMMENT,
nVARIANT,
nFLD_NAME,
nPASSUP,
nOCONSTANT,
nPNAME,
nSPECIAL,
nROUTNAME,
nABSID,
 0};
 /* cpp definitions */