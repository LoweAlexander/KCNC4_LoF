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
 
#define nrn_init _nrn_init__Kv3_3
#define _nrn_initial _nrn_initial__Kv3_3
#define nrn_cur _nrn_cur__Kv3_3
#define _nrn_current _nrn_current__Kv3_3
#define nrn_jacob _nrn_jacob__Kv3_3
#define nrn_state _nrn_state__Kv3_3
#define _net_receive _net_receive__Kv3_3 
#define rateConst rateConst__Kv3_3 
#define state state__Kv3_3 
 
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
#define gateCurrent _p[0]
#define gateCurrent_columnindex 0
#define gbar _p[1]
#define gbar_columnindex 1
#define gunit _p[2]
#define gunit_columnindex 2
#define ik _p[3]
#define ik_columnindex 3
#define igate _p[4]
#define igate_columnindex 4
#define i _p[5]
#define i_columnindex 5
#define g _p[6]
#define g_columnindex 6
#define nc _p[7]
#define nc_columnindex 7
#define ninf _p[8]
#define ninf_columnindex 8
#define taun _p[9]
#define taun_columnindex 9
#define n _p[10]
#define n_columnindex 10
#define ek _p[11]
#define ek_columnindex 11
#define qt _p[12]
#define qt_columnindex 12
#define alpha _p[13]
#define alpha_columnindex 13
#define beta _p[14]
#define beta_columnindex 14
#define Dn _p[15]
#define Dn_columnindex 15
#define v _p[16]
#define v_columnindex 16
#define _g _p[17]
#define _g_columnindex 17
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
 static void _hoc_alphaFkt(void);
 static void _hoc_betaFkt(void);
 static void _hoc_ngateFlip(void);
 static void _hoc_rateConst(void);
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
 "setdata_Kv3_3", _hoc_setdata,
 "alphaFkt_Kv3_3", _hoc_alphaFkt,
 "betaFkt_Kv3_3", _hoc_betaFkt,
 "ngateFlip_Kv3_3", _hoc_ngateFlip,
 "rateConst_Kv3_3", _hoc_rateConst,
 0, 0
};
#define alphaFkt alphaFkt_Kv3_3
#define betaFkt betaFkt_Kv3_3
#define ngateFlip ngateFlip_Kv3_3
 extern double alphaFkt( _threadargsprotocomma_ double );
 extern double betaFkt( _threadargsprotocomma_ double );
 extern double ngateFlip( _threadargsproto_ );
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "gbar_Kv3_3", 0, 1e+09,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gateCurrent_Kv3_3", "1",
 "gbar_Kv3_3", "S/cm2",
 "gunit_Kv3_3", "pS",
 "ik_Kv3_3", "mA/cm2",
 "igate_Kv3_3", "mA/cm2",
 "i_Kv3_3", "mA/cm2",
 "g_Kv3_3", "S/cm2",
 "nc_Kv3_3", "1/cm2",
 "ninf_Kv3_3", "1",
 "taun_Kv3_3", "ms",
 0,0
};
 static double delta_t = 0.01;
 static double n0 = 0;
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
"Kv3_3",
 "gateCurrent_Kv3_3",
 "gbar_Kv3_3",
 "gunit_Kv3_3",
 0,
 "ik_Kv3_3",
 "igate_Kv3_3",
 "i_Kv3_3",
 "g_Kv3_3",
 "nc_Kv3_3",
 "ninf_Kv3_3",
 "taun_Kv3_3",
 0,
 "n_Kv3_3",
 0,
 0};
 static Symbol* _k_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 18, _prop);
 	/*initialize range parameters*/
 	gateCurrent = 0;
 	gbar = 0.005;
 	gunit = 16;
 	_prop->param = _p;
 	_prop->param_size = 18;
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
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _Kv33_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("k", -10000.);
 	_k_sym = hoc_lookup("k_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 18, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 Kv3_3 Kv33.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double e0 = 1.60217646e-19;
 static double q10 = 2.7;
 static double ca = 0.22;
 static double cva = 16;
 static double cka = -26.5;
 static double cb = 0.22;
 static double cvb = 16;
 static double ckb = 26.5;
 static double zn = 1.9196;
static int _reset;
static char *modelname = "Voltage-gated potassium channel from Kv3 subunits";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rateConst(_threadargsprotocomma_ double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[1], _dlist1[1];
 static int state(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset = 0; {
   rateConst ( _threadargscomma_ v ) ;
   Dn = alpha * ( 1.0 - n ) - beta * n ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
 rateConst ( _threadargscomma_ v ) ;
 Dn = Dn  / (1. - dt*( ( alpha )*( ( ( - 1.0 ) ) ) - ( beta )*( 1.0 ) )) ;
  return 0;
}
 /*END CVODE*/
 static int state (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) { {
   rateConst ( _threadargscomma_ v ) ;
    n = n + (1. - exp(dt*(( alpha )*( ( ( - 1.0 ) ) ) - ( beta )*( 1.0 ))))*(- ( ( alpha )*( ( 1.0 ) ) ) / ( ( alpha )*( ( ( - 1.0 ) ) ) - ( beta )*( 1.0 ) ) - n) ;
   }
  return 0;
}
 
static int  rateConst ( _threadargsprotocomma_ double _lv ) {
   alpha = qt * alphaFkt ( _threadargscomma_ _lv ) ;
   beta = qt * betaFkt ( _threadargscomma_ _lv ) ;
   ninf = alpha / ( alpha + beta ) ;
   taun = 1.0 / ( alpha + beta ) ;
    return 0; }
 
static void _hoc_rateConst(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 rateConst ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double alphaFkt ( _threadargsprotocomma_ double _lv ) {
   double _lalphaFkt;
 _lalphaFkt = ca * exp ( - ( _lv + cva ) / cka ) ;
   
return _lalphaFkt;
 }
 
static void _hoc_alphaFkt(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  alphaFkt ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double betaFkt ( _threadargsprotocomma_ double _lv ) {
   double _lbetaFkt;
 _lbetaFkt = cb * exp ( - ( _lv + cvb ) / ckb ) ;
   
return _lbetaFkt;
 }
 
static void _hoc_betaFkt(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  betaFkt ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double ngateFlip ( _threadargsproto_ ) {
   double _lngateFlip;
 _lngateFlip = ( ninf - n ) / taun ;
   
return _lngateFlip;
 }
 
static void _hoc_ngateFlip(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  ngateFlip ( _p, _ppvar, _thread, _nt );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 1;}
 
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
	for (_i=0; _i < 1; ++_i) {
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
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_k_sym, _ppvar, 0, 0);
   nrn_update_ion_pointer(_k_sym, _ppvar, 1, 3);
   nrn_update_ion_pointer(_k_sym, _ppvar, 2, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
  n = n0;
 {
   nc = ( 1e12 ) * gbar / gunit ;
   qt = pow( q10 , ( ( celsius - 22.0 ) / 10.0 ) ) ;
   rateConst ( _threadargscomma_ v ) ;
   n = ninf ;
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
   g = gbar * pow( n , 4.0 ) ;
   ik = g * ( v - ek ) ;
   igate = nc * ( 1e6 ) * e0 * 4.0 * zn * ngateFlip ( _threadargs_ ) ;
   if ( gateCurrent  != 0.0 ) {
     i = igate ;
     }
   }
 _current += ik;
 _current += i;

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
 {   state(_p, _ppvar, _thread, _nt);
  } }}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = n_columnindex;  _dlist1[0] = Dn_columnindex;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "Kv33.mod";
static const char* nmodl_file_text = 
  "TITLE Voltage-gated potassium channel from Kv3 subunits\n"
  "\n"
  "COMMENT\n"
  "Voltage-gated potassium channel with high threshold and fast activation/deactivation kinetics\n"
  "\n"
  "KINETIC SCHEME: Hodgkin-Huxley (n^4)\n"
  "n'= alpha * (1-n) - betha * n\n"
  "g(v) = gbar * n^4 * ( v-ek )\n"
  "\n"
  "The rate constants of activation (alpha) and deactivation (beta) were approximated by:\n"
  "\n"
  "alpha(v) = ca * exp(-(v+cva)/cka)\n"
  "beta(v) = cb * exp(-(v+cvb)/ckb)\n"
  "\n"
  "Parameters can, cvan, ckan, cbn, cvbn, ckbn are given in the CONSTANT block.\n"
  "Values derive from least-square fits to experimental data of G/Gmax(v) and taun(v) in Martina et al. J Neurophys. 97 (563-671, 2007.\n"
  "Model includes a calculation of Kv gating current\n"
  "\n"
  "Reference: Akemann et al., Biophys. J. (2009) 96: 3959-3976\n"
  "\n"
  "Laboratory for Neuronal Circuit Dynamics\n"
  "RIKEN Brain Science Institute, Wako City, Japan\n"
  "http://www.neurodynamics.brain.riken.jp\n"
  "\n"
  "Date of Implementation: April 2007\n"
  "Contact: akemann@brain.riken.jp\n"
  "\n"
  "Suffix from Kv3 to Kv3_3\n"
  "\n"
  "ENDCOMMENT\n"
  "\n"
  "\n"
  "NEURON {\n"
  "    THREADSAFE\n"
  "	SUFFIX Kv3_3\n"
  "	USEION k READ ek WRITE ik\n"
  "	NONSPECIFIC_CURRENT i\n"
  "	RANGE gbar, g, ik, i, igate, nc\n"
  "	RANGE ninf, taun\n"
  "	RANGE gateCurrent, gunit\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "	(mV) = (millivolt)\n"
  "	(mA) = (milliamp)\n"
  "	(nA) = (nanoamp)\n"
  "	(pA) = (picoamp)\n"
  "	(S)  = (siemens)\n"
  "	(mS) = (millisiemens)\n"
  "	(nS) = (nanosiemens)\n"
  "	(pS) = (picosiemens)\n"
  "	(um) = (micron)\n"
  "	(molar) = (1/liter)\n"
  "	(mM) = (millimolar)		\n"
  "}\n"
  "\n"
  "CONSTANT {\n"
  "	e0 = 1.60217646e-19 (coulombs)\n"
  "	q10 = 2.7\n"
  "\n"
  "	ca = 0.22 (1/ms)\n"
  "	cva = 16 (mV)\n"
  "	cka = -26.5 (mV)\n"
  "	cb = 0.22 (1/ms)\n"
  "	cvb = 16 (mV)\n"
  "	ckb = 26.5 (mV)\n"
  "	\n"
  "	zn = 1.9196 (1)		: valence of n-gate\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "	gateCurrent = 0 (1)	: gating currents ON = 1 OFF = 0\n"
  "	\n"
  "	gbar = 0.005 (S/cm2)   <0,1e9>\n"
  "	gunit = 16 (pS)		: unitary conductance \n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	celsius (degC)\n"
  "	v (mV)\n"
  "	\n"
  "	ik (mA/cm2)\n"
  "	igate (mA/cm2)\n"
  "	i (mA/cm2)\n"
  " \n"
  "	ek (mV)\n"
  "	g (S/cm2)\n"
  "	nc (1/cm2)\n"
  "	qt (1)\n"
  "\n"
  "	ninf (1)\n"
  "	taun (ms)\n"
  "	alpha (1/ms)\n"
  "	beta (1/ms)\n"
  "}\n"
  "\n"
  "STATE { n }\n"
  "\n"
  "INITIAL {\n"
  "	nc = (1e12) * gbar / gunit\n"
  "	qt = q10^((celsius-22 (degC))/10 (degC))\n"
  "	rateConst(v)\n"
  "	n = ninf\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE state METHOD cnexp\n"
  "      g = gbar * n^4 \n"
  "	ik = g * (v - ek)\n"
  "	igate = nc * (1e6) * e0 * 4 * zn * ngateFlip()\n"
  "\n"
  "	if (gateCurrent != 0) { \n"
  "		i = igate\n"
  "	}\n"
  "}\n"
  "\n"
  "DERIVATIVE state {\n"
  "	rateConst(v)\n"
  "	n' = alpha * (1-n) - beta * n\n"
  "}\n"
  "\n"
  "PROCEDURE rateConst(v (mV)) {\n"
  "	alpha = qt * alphaFkt(v)\n"
  "	beta = qt * betaFkt(v)\n"
  "	ninf = alpha / (alpha + beta) \n"
  "	taun = 1 / (alpha + beta)\n"
  "}\n"
  "\n"
  "FUNCTION alphaFkt(v (mV)) (1/ms) {\n"
  "	alphaFkt = ca * exp(-(v+cva)/cka) \n"
  "}\n"
  "\n"
  "FUNCTION betaFkt(v (mV)) (1/ms) {\n"
  "	betaFkt = cb * exp(-(v+cvb)/ckb)\n"
  "}\n"
  "\n"
  "FUNCTION ngateFlip() (1/ms) {\n"
  "	ngateFlip = (ninf-n)/taun \n"
  "}\n"
  "\n"
  "\n"
  ;
#endif
