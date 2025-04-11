/* Created by Language version: 7.7.0 */
/* VECTORIZED */
#define NRN_VECTORIZED 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mech_api.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__Kv1_5
#define _nrn_initial _nrn_initial__Kv1_5
#define nrn_cur _nrn_cur__Kv1_5
#define _nrn_current _nrn_current__Kv1_5
#define nrn_jacob _nrn_jacob__Kv1_5
#define nrn_state _nrn_state__Kv1_5
#define _net_receive _net_receive__Kv1_5 
#define rates rates__Kv1_5 
#define states states__Kv1_5 
 
#define _threadargscomma_ _p, _ppvar, _thread, _nt,
#define _threadargsprotocomma_ double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt,
#define _threadargs_ _p, _ppvar, _thread, _nt
#define _threadargsproto_ double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 /* Thread safe. No static _p or _ppvar. */
 
#define t _nt->_t
#define dt _nt->_dt
#define gKur _p[0]
#define gKur_columnindex 0
#define Tauact _p[1]
#define Tauact_columnindex 1
#define Tauinactf _p[2]
#define Tauinactf_columnindex 2
#define Tauinacts _p[3]
#define Tauinacts_columnindex 3
#define ik _p[4]
#define ik_columnindex 4
#define minf _p[5]
#define minf_columnindex 5
#define ninf _p[6]
#define ninf_columnindex 6
#define uinf _p[7]
#define uinf_columnindex 7
#define mtau _p[8]
#define mtau_columnindex 8
#define ntau _p[9]
#define ntau_columnindex 9
#define utau _p[10]
#define utau_columnindex 10
#define ino _p[11]
#define ino_columnindex 11
#define ki _p[12]
#define ki_columnindex 12
#define ko _p[13]
#define ko_columnindex 13
#define nai _p[14]
#define nai_columnindex 14
#define nao _p[15]
#define nao_columnindex 15
#define m _p[16]
#define m_columnindex 16
#define n _p[17]
#define n_columnindex 17
#define u _p[18]
#define u_columnindex 18
#define Dm _p[19]
#define Dm_columnindex 19
#define Dn _p[20]
#define Dn_columnindex 20
#define Du _p[21]
#define Du_columnindex 21
#define ek _p[22]
#define ek_columnindex 22
#define v _p[23]
#define v_columnindex 23
#define _g _p[24]
#define _g_columnindex 24
#define _ion_ek	*_ppvar[0]._pval
#define _ion_ik	*_ppvar[1]._pval
#define _ion_dikdv	*_ppvar[2]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  -1;
 static Datum* _extcall_thread;
 static Prop* _extcall_prop;
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static void _hoc_alp(void);
 static void _hoc_bet(void);
 static void _hoc_ce(void);
 static void _hoc_rates(void);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static const char* nmodl_file_text;
static const char* nmodl_filename;
extern void hoc_reg_nmodl_text(int, const char*);
extern void hoc_reg_nmodl_filename(int, const char*);
#endif

 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _extcall_prop = _prop;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_Kv1_5", _hoc_setdata,
 "alp_Kv1_5", _hoc_alp,
 "bet_Kv1_5", _hoc_bet,
 "ce_Kv1_5", _hoc_ce,
 "rates_Kv1_5", _hoc_rates,
 0, 0
};
#define alp alp_Kv1_5
#define bet bet_Kv1_5
#define ce ce_Kv1_5
 extern double alp( _threadargsprotocomma_ double , double );
 extern double bet( _threadargsprotocomma_ double , double );
 extern double ce( _threadargsprotocomma_ double , double );
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "gKur_Kv1_5", 0, 1e+09,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gKur_Kv1_5", "S/cm2",
 "Tauact_Kv1_5", "ms",
 "Tauinactf_Kv1_5", "ms",
 "Tauinacts_Kv1_5", "ms",
 "ik_Kv1_5", "mA/cm2",
 "mtau_Kv1_5", "ms",
 "ntau_Kv1_5", "ms",
 "utau_Kv1_5", "ms",
 "ino_Kv1_5", "mA/cm2",
 "ki_Kv1_5", "mM",
 "ko_Kv1_5", "mM",
 "nai_Kv1_5", "mM",
 "nao_Kv1_5", "mM",
 0,0
};
 static double delta_t = 0.01;
 static double m0 = 0;
 static double n0 = 0;
 static double u0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(NrnThread*, _Memb_list*, int);
static void nrn_state(NrnThread*, _Memb_list*, int);
 static void nrn_cur(NrnThread*, _Memb_list*, int);
static void  nrn_jacob(NrnThread*, _Memb_list*, int);
 
static int _ode_count(int);
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(NrnThread*, _Memb_list*, int);
static void _ode_matsol(NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[3]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"Kv1_5",
 "gKur_Kv1_5",
 "Tauact_Kv1_5",
 "Tauinactf_Kv1_5",
 "Tauinacts_Kv1_5",
 0,
 "ik_Kv1_5",
 "minf_Kv1_5",
 "ninf_Kv1_5",
 "uinf_Kv1_5",
 "mtau_Kv1_5",
 "ntau_Kv1_5",
 "utau_Kv1_5",
 "ino_Kv1_5",
 "ki_Kv1_5",
 "ko_Kv1_5",
 "nai_Kv1_5",
 "nao_Kv1_5",
 0,
 "m_Kv1_5",
 "n_Kv1_5",
 "u_Kv1_5",
 0,
 0};
 static Symbol* _k_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 25, _prop);
 	/*initialize range parameters*/
 	gKur = 0.00013195;
 	Tauact = 1;
 	Tauinactf = 1;
 	Tauinacts = 1;
 	_prop->param = _p;
 	_prop->param_size = 25;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_k_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[0]._pval = &prop_ion->param[0]; /* ek */
 	_ppvar[1]._pval = &prop_ion->param[3]; /* ik */
 	_ppvar[2]._pval = &prop_ion->param[4]; /* _ion_dikdv */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _thread_mem_init(Datum*);
 static void _thread_cleanup(Datum*);
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _Kv15_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("k", -10000.);
 	_k_sym = hoc_lookup("k_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 5);
  _extcall_thread = (Datum*)ecalloc(4, sizeof(Datum));
  _thread_mem_init(_extcall_thread);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 1, _thread_mem_init);
     _nrn_thread_reg(_mechtype, 0, _thread_cleanup);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 25, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 Kv1_5 Kv15.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 
#define F _nrnunit_F[_nrnunit_use_legacy_]
static double _nrnunit_F[2] = {0x1.78e555060882cp+16, 96485.3}; /* 96485.3321233100141 */
 
#define R _nrnunit_R[_nrnunit_use_legacy_]
static double _nrnunit_R[2] = {0x1.0a1013e8990bep+3, 8.3145}; /* 8.3144626181532395 */
static int _reset;
static char *modelname = "Cardiac IKur  current & nonspec cation current with identical kinetics";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rates(_threadargsprotocomma_ double);
 
#define _deriv1_advance _thread[0]._i
#define _dith1 1
#define _recurse _thread[2]._i
#define _newtonspace1 _thread[3]._pvoid
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist2[3];
  static int _slist1[3], _dlist1[3];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset = 0; {
   rates ( _threadargscomma_ v ) ;
   Dm = ( minf - m ) / mtau ;
   Dn = ( ninf - n ) / ntau ;
   Du = ( uinf - u ) / utau ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
 rates ( _threadargscomma_ v ) ;
 Dm = Dm  / (1. - dt*( ( ( ( - 1.0 ) ) ) / mtau )) ;
 Dn = Dn  / (1. - dt*( ( ( ( - 1.0 ) ) ) / ntau )) ;
 Du = Du  / (1. - dt*( ( ( ( - 1.0 ) ) ) / utau )) ;
  return 0;
}
 /*END CVODE*/
 
static int states (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset=0; int error = 0;
 { double* _savstate1 = _thread[_dith1]._pval;
 double* _dlist2 = _thread[_dith1]._pval + 3;
 int _counte = -1;
 if (!_recurse) {
 _recurse = 1;
 {int _id; for(_id=0; _id < 3; _id++) { _savstate1[_id] = _p[_slist1[_id]];}}
 error = nrn_newton_thread(_newtonspace1, 3,_slist2, _p, states, _dlist2, _ppvar, _thread, _nt);
 _recurse = 0; if(error) {abort_run(error);}}
 {
   rates ( _threadargscomma_ v ) ;
   Dm = ( minf - m ) / mtau ;
   Dn = ( ninf - n ) / ntau ;
   Du = ( uinf - u ) / utau ;
   {int _id; for(_id=0; _id < 3; _id++) {
if (_deriv1_advance) {
 _dlist2[++_counte] = _p[_dlist1[_id]] - (_p[_slist1[_id]] - _savstate1[_id])/dt;
 }else{
_dlist2[++_counte] = _p[_slist1[_id]] - _savstate1[_id];}}}
 } }
 return _reset;}
 
double alp ( _threadargsprotocomma_ double _lv , double _li ) {
   double _lalp;
 double _lq10 ;
 _lv = _lv ;
   _lq10 = pow( 2.2 , ( ( celsius - 37.0 ) / 10.0 ) ) ;
   if ( _li  == 0.0 ) {
     _lalp = _lq10 * 0.65 / ( exp ( - ( _lv + 10.0 ) / 8.5 ) + exp ( - ( _lv - 30.0 ) / 59.0 ) ) ;
     }
   else if ( _li  == 1.0 ) {
     _lalp = 0.001 * _lq10 / ( 2.4 + 10.9 * exp ( - ( _lv + 90.0 ) / 78.0 ) ) ;
     }
   
return _lalp;
 }
 
static void _hoc_alp(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  alp ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
double bet ( _threadargsprotocomma_ double _lv , double _li ) {
   double _lbet;
 double _lq10 ;
 _lv = _lv ;
   _lq10 = pow( 2.2 , ( ( celsius - 37.0 ) / 10.0 ) ) ;
   if ( _li  == 0.0 ) {
     _lbet = _lq10 * 0.65 / ( 2.5 + exp ( ( _lv + 82.0 ) / 17.0 ) ) ;
     }
   else if ( _li  == 1.0 ) {
     _lbet = _lq10 * 0.001 * exp ( ( _lv - 168.0 ) / 16.0 ) ;
     }
   
return _lbet;
 }
 
static void _hoc_bet(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  bet ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
double ce ( _threadargsprotocomma_ double _lv , double _li ) {
   double _lce;
 _lv = _lv ;
   if ( _li  == 0.0 ) {
     _lce = 1.0 / ( 1.0 + exp ( - ( _lv + 30.3 ) / 9.6 ) ) ;
     }
   else if ( _li  == 1.0 ) {
     _lce = 1.0 * ( 0.25 + 1.0 / ( 1.35 + exp ( ( _lv + 7.0 ) / 14.0 ) ) ) ;
     }
   else if ( _li  == 2.0 ) {
     _lce = 1.0 * ( 0.1 + 1.0 / ( 1.1 + exp ( ( _lv + 7.0 ) / 14.0 ) ) ) ;
     }
   
return _lce;
 }
 
static void _hoc_ce(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  ce ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
static int  rates ( _threadargsprotocomma_ double _lv ) {
   double _la , _lb , _lc ;
 _la = alp ( _threadargscomma_ _lv , 0.0 ) ;
   _lb = bet ( _threadargscomma_ _lv , 0.0 ) ;
   _lc = ce ( _threadargscomma_ _lv , 0.0 ) ;
   mtau = 1.0 / ( _la + _lb ) / 3.0 * Tauact ;
   minf = _lc ;
   _la = alp ( _threadargscomma_ _lv , 1.0 ) ;
   _lb = bet ( _threadargscomma_ _lv , 1.0 ) ;
   _lc = ce ( _threadargscomma_ _lv , 1.0 ) ;
   ntau = 1.0 / ( _la + _lb ) / 3.0 * Tauinactf ;
   ninf = _lc ;
   _lc = ce ( _threadargscomma_ _lv , 2.0 ) ;
   uinf = _lc ;
   utau = 6800.0 * Tauinacts ;
    return 0; }
 
static void _hoc_rates(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 rates ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 3;}
 
static void _ode_spec(NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  ek = _ion_ek;
     _ode_spec1 (_p, _ppvar, _thread, _nt);
  }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 3; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _ode_matsol1 (_p, _ppvar, _thread, _nt);
 }
 
static void _ode_matsol(NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  ek = _ion_ek;
 _ode_matsol_instance1(_threadargs_);
 }}
 
static void _thread_mem_init(Datum* _thread) {
   _thread[_dith1]._pval = (double*)ecalloc(6, sizeof(double));
   _newtonspace1 = nrn_cons_newtonspace(3);
 }
 
static void _thread_cleanup(Datum* _thread) {
   free((void*)(_thread[_dith1]._pval));
   nrn_destroy_newtonspace(_newtonspace1);
 }
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_k_sym, _ppvar, 0, 0);
   nrn_update_ion_pointer(_k_sym, _ppvar, 1, 3);
   nrn_update_ion_pointer(_k_sym, _ppvar, 2, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
  m = m0;
  n = n0;
  u = u0;
 {
   rates ( _threadargscomma_ v ) ;
   m = minf ;
   n = ninf ;
   u = uinf ;
   }
 
}
}

static void nrn_init(NrnThread* _nt, _Memb_list* _ml, int _type){
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
  ek = _ion_ek;
 initmodel(_p, _ppvar, _thread, _nt);
 }
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   double _lz ;
 _lz = ( R * ( celsius + 273.15 ) ) / F ;
   ik = gKur * ( ( 0.1 + 1.0 / ( 1.0 + exp ( - ( v - 15.0 ) / 13.0 ) ) ) * m * m * m * n * u * ( v - ek ) ) ;
   }
 _current += ik;

} return _current;
}

static void nrn_cur(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
  ek = _ion_ek;
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ double _dik;
  _dik = ik;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_dikdv += (_dik - ik)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ik += ik ;
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}
 
}

static void nrn_jacob(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}
 
}

static void nrn_state(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
double _dtsav = dt;
if (secondorder) { dt *= 0.5; }
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v=_v;
{
  ek = _ion_ek;
 {  _deriv1_advance = 1;
 derivimplicit_thread(3, _slist1, _dlist1, _p, states, _ppvar, _thread, _nt);
_deriv1_advance = 0;
     if (secondorder) {
    int _i;
    for (_i = 0; _i < 3; ++_i) {
      _p[_slist1[_i]] += dt*_p[_dlist1[_i]];
    }}
 } }}
 dt = _dtsav;
}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = m_columnindex;  _dlist1[0] = Dm_columnindex;
 _slist1[1] = n_columnindex;  _dlist1[1] = Dn_columnindex;
 _slist1[2] = u_columnindex;  _dlist1[2] = Du_columnindex;
 _slist2[0] = m_columnindex;
 _slist2[1] = n_columnindex;
 _slist2[2] = u_columnindex;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "Kv15.mod";
static const char* nmodl_file_text = 
  "TITLE Cardiac IKur  current & nonspec cation current with identical kinetics\n"
  ": Hodgkin - Huxley type channels, modified to fit IKur data from Feng et al Am J Physiol 1998 275:H1717 - H 1725\n"
  ": Suffix from Kv15 to Kv1_5\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX Kv1_5\n"
  "	USEION k READ ek WRITE ik : is not working with ,ki,ko\n"
  "	:USEION na READ nai,nao\n"
  "	:USEION no WRITE ino VALENCE 1: nonspecific cation current\n"
  "	RANGE gKur, ik, ino, Tauact, Tauinactf,Tauinacts, gnonspec, nao, nai, ko,ki\n"
  "	RANGE minf, ninf, uinf, mtau , ntau, utau\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "	(mA) = (milliamp)\n"
  "	(mV) = (millivolt)\n"
  "        (mM) = (milli/liter)\n"
  "	F = (faraday) (coulombs)\n"
  "	R 	= (k-mole)	(joule/degC)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "	 gKur= 0.13195e-3 (S/cm2) <0,1e9>\n"
  "	Tauact=1 (ms)\n"
  "	Tauinactf=1 (ms)\n"
  "	Tauinacts=1 (ms)\n"
  "	:gnonspec=0   (S/cm2) <0,1e9>\n"
  "}\n"
  "STATE {\n"
  "	 m n u\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	v (mV)\n"
  "	celsius (degC) : 37\n"
  "    ik (mA/cm2)\n"
  "	minf ninf uinf\n"
  "	mtau (ms)\n"
  "    ntau (ms)\n"
  "	utau (ms)\n"
  "	ek (mV)\n"
  "	ino (mA/cm2)\n"
  "	ki (mM)\n"
  "	ko (mM)\n"
  "	nai (mM)\n"
  "	nao (mM)\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	rates(v)\n"
  "	m = minf\n"
  "    n = ninf\n"
  "	u = uinf\n"
  "}\n"
  "\n"
  "BREAKPOINT { LOCAL z\n"
  "	z = (R*(celsius+273.15))/F\n"
  "	SOLVE states METHOD derivimplicit\n"
  "    ik = gKur*((0.1 + 1/(1 + exp(-(v - 15)/13)))*m*m*m*n*u*(v - ek))\n"
  "	:ino=gnonspec*(0.1 + 1/(1 + exp(-(v - 15)/13)))*m*m*m*n*u*(v - z*log((nao+ko)/(nai+ki)))\n"
  "	\n"
  "    :printf(\"ik: %g \\n\", ik)\n"
  "}\n"
  "\n"
  "DERIVATIVE states {	: exact when v held constant\n"
  "	rates(v)\n"
  "	m' = (minf - m)/mtau\n"
  "    n' = (ninf - n)/ntau\n"
  "	u' = (uinf - u)/utau\n"
  "}\n"
  "\n"
  "UNITSOFF\n"
  "FUNCTION alp(v(mV),i) { LOCAL q10 : order m n\n"
  "	v = v\n"
  "	q10 = 2.2^((celsius - 37)/10)\n"
  "       if (i==0) {\n"
  "	          alp = q10*0.65/(exp(-(v + 10)/8.5) + exp(-(v - 30)/59))\n"
  "          } else if (i==1) {\n"
  "                   alp = 0.001*q10/(2.4 +10.9* exp(-(v + 90)/78))\n"
  "          }\n"
  "	\n"
  "}\n"
  "\n"
  "FUNCTION bet(v(mV),i) (/ms) { LOCAL q10 : order m n u\n"
  "	v = v \n"
  "	q10 = 2.2^((celsius - 37)/10)\n"
  "        if (i==0){\n"
  "	         bet = q10*0.65/(2.5 + exp((v + 82)/17))\n"
  "        }else if (i==1){\n"
  "                  bet = q10*0.001*exp((v - 168)/16)\n"
  "        }\n"
  "}\n"
  "                \n"
  "FUNCTION ce(v(mV),i)(/ms) {   :  order m n u \n"
  "        v = v\n"
  "       \n"
  "        if (i==0) {\n"
  "                ce = 1/(1 + exp(-(v + 30.3)/9.6))\n"
  "        }else if (i==1){\n"
  "                ce = 1*(0.25+1/(1.35 + exp((v + 7)/14)))\n"
  "       \n"
  "        }else if (i==2){\n"
  "                ce = 1*(0.1+1/(1.1 + exp((v + 7)/14)))\n"
  "        }\n"
  "}\n"
  "\n"
  "\n"
  "PROCEDURE rates(v) {LOCAL a,b,c :\n"
  "	\n"
  "		a = alp(v,0)  b=bet(v,0) c = ce(v,0)\n"
  "		mtau = 1/(a + b)/3*Tauact\n"
  "		minf = c\n"
  "               a = alp(v,1)  b=bet(v,1) c = ce(v,1)\n"
  "		ntau = 1/(a + b)/3*Tauinactf\n"
  "		ninf = c\n"
  "		c = ce(v,2)\n"
  "		uinf = c\n"
  "		utau = 6800*Tauinacts\n"
  "}\n"
  "UNITSON\n"
  ;
#endif
