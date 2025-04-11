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
 
#define nrn_init _nrn_init__Cav3_3
#define _nrn_initial _nrn_initial__Cav3_3
#define nrn_cur _nrn_cur__Cav3_3
#define _nrn_current _nrn_current__Cav3_3
#define nrn_jacob _nrn_jacob__Cav3_3
#define nrn_state _nrn_state__Cav3_3
#define _net_receive _net_receive__Cav3_3 
#define rates rates__Cav3_3 
#define states states__Cav3_3 
 
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
#define gCav3_3bar _p[0]
#define gCav3_3bar_columnindex 0
#define pcabar _p[1]
#define pcabar_columnindex 1
#define ica _p[2]
#define ica_columnindex 2
#define n_inf _p[3]
#define n_inf_columnindex 3
#define tau_n _p[4]
#define tau_n_columnindex 4
#define l_inf _p[5]
#define l_inf_columnindex 5
#define tau_l _p[6]
#define tau_l_columnindex 6
#define n _p[7]
#define n_columnindex 7
#define l _p[8]
#define l_columnindex 8
#define gCav3_3 _p[9]
#define gCav3_3_columnindex 9
#define cai _p[10]
#define cai_columnindex 10
#define cao _p[11]
#define cao_columnindex 11
#define qt _p[12]
#define qt_columnindex 12
#define T _p[13]
#define T_columnindex 13
#define ghk _p[14]
#define ghk_columnindex 14
#define w _p[15]
#define w_columnindex 15
#define Dn _p[16]
#define Dn_columnindex 16
#define Dl _p[17]
#define Dl_columnindex 17
#define v _p[18]
#define v_columnindex 18
#define _g _p[19]
#define _g_columnindex 19
#define _ion_cai	*_ppvar[0]._pval
#define _ion_cao	*_ppvar[1]._pval
#define _ion_ica	*_ppvar[2]._pval
#define _ion_dicadv	*_ppvar[3]._pval
 
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
 "setdata_Cav3_3", _hoc_setdata,
 "rates_Cav3_3", _hoc_rates,
 0, 0
};
 /* declare global and static user variables */
#define F F_Cav3_3
 double F = 96520;
#define PI PI_Cav3_3
 double PI = 3.14;
#define R R_Cav3_3
 double R = 8.3134;
#define kl kl_Cav3_3
 double kl = -6.1;
#define kn kn_Cav3_3
 double kn = 6.2;
#define q10 q10_Cav3_3
 double q10 = 2.3;
#define vhalfl vhalfl_Cav3_3
 double vhalfl = -69.8;
#define vhalfn vhalfn_Cav3_3
 double vhalfn = -41.5;
#define z z_Cav3_3
 double z = 2;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gCav3_3bar_Cav3_3", "S/cm2",
 "ica_Cav3_3", "mA/cm2",
 0,0
};
 static double delta_t = 0.01;
 static double l0 = 0;
 static double n0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "vhalfn_Cav3_3", &vhalfn_Cav3_3,
 "vhalfl_Cav3_3", &vhalfl_Cav3_3,
 "kn_Cav3_3", &kn_Cav3_3,
 "kl_Cav3_3", &kl_Cav3_3,
 "q10_Cav3_3", &q10_Cav3_3,
 "z_Cav3_3", &z_Cav3_3,
 "F_Cav3_3", &F_Cav3_3,
 "R_Cav3_3", &R_Cav3_3,
 "PI_Cav3_3", &PI_Cav3_3,
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
 
#define _cvode_ieq _ppvar[4]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"Cav3_3",
 "gCav3_3bar_Cav3_3",
 "pcabar_Cav3_3",
 0,
 "ica_Cav3_3",
 "n_inf_Cav3_3",
 "tau_n_Cav3_3",
 "l_inf_Cav3_3",
 "tau_l_Cav3_3",
 0,
 "n_Cav3_3",
 "l_Cav3_3",
 0,
 0};
 static Symbol* _ca_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 20, _prop);
 	/*initialize range parameters*/
 	gCav3_3bar = 1e-05;
 	pcabar = 0.0001;
 	_prop->param = _p;
 	_prop->param_size = 20;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 5, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_ca_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[0]._pval = &prop_ion->param[1]; /* cai */
 	_ppvar[1]._pval = &prop_ion->param[2]; /* cao */
 	_ppvar[2]._pval = &prop_ion->param[3]; /* ica */
 	_ppvar[3]._pval = &prop_ion->param[4]; /* _ion_dicadv */
 
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

 void _Cav3_3_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("ca", -10000.);
 	_ca_sym = hoc_lookup("ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 20, 5);
  hoc_register_dparam_semantics(_mechtype, 0, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 Cav3_3 Cav3_3.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "CaV 3.3 CA3 hippocampal neuron";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rates(_threadargsproto_);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[2], _dlist1[2];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset = 0; {
   rates ( _threadargs_ ) ;
   Dn = ( n_inf - n ) / tau_n ;
   Dl = ( l_inf - l ) / tau_l ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
 rates ( _threadargs_ ) ;
 Dn = Dn  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_n )) ;
 Dl = Dl  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_l )) ;
  return 0;
}
 /*END CVODE*/
 static int states (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) { {
   rates ( _threadargs_ ) ;
    n = n + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_n)))*(- ( ( ( n_inf ) ) / tau_n ) / ( ( ( ( - 1.0 ) ) ) / tau_n ) - n) ;
    l = l + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_l)))*(- ( ( ( l_inf ) ) / tau_l ) / ( ( ( ( - 1.0 ) ) ) / tau_l ) - l) ;
   }
  return 0;
}
 
static int  rates ( _threadargsproto_ ) {
   n_inf = 1.0 / ( 1.0 + exp ( - ( v - vhalfn ) / kn ) ) ;
   l_inf = 1.0 / ( 1.0 + exp ( - ( v - vhalfl ) / kl ) ) ;
   if ( v > - 60.0 ) {
     tau_n = ( 7.2 + 0.02 * exp ( - v / 14.7 ) ) / qt ;
     tau_l = ( 79.5 + 2.0 * exp ( - v / 9.3 ) ) / qt ;
     }
   else {
     tau_n = ( 0.875 * exp ( ( v + 120.0 ) / 41.0 ) ) / qt ;
     tau_l = 260.0 / qt ;
     }
   w = v * 0.001 * z * F / ( R * T ) ;
   ghk = - 0.001 * z * F * ( cao - cai * exp ( w ) ) * w / ( exp ( w ) - 1.0 ) ;
    return 0; }
 
static void _hoc_rates(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 rates ( _p, _ppvar, _thread, _nt );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 2;}
 
static void _ode_spec(NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  cai = _ion_cai;
  cao = _ion_cao;
     _ode_spec1 (_p, _ppvar, _thread, _nt);
  }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 2; ++_i) {
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
  cai = _ion_cai;
  cao = _ion_cao;
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_ca_sym, _ppvar, 0, 1);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 1, 2);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 2, 3);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 3, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
  l = l0;
  n = n0;
 {
   T = celsius + 273.14 ;
   qt = pow ( q10 , ( celsius - 28.0 ) / 10.0 ) ;
   rates ( _threadargs_ ) ;
   n = n_inf ;
   l = l_inf ;
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
  cai = _ion_cai;
  cao = _ion_cao;
 initmodel(_p, _ppvar, _thread, _nt);
 }
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   ica = gCav3_3bar * pcabar * n * n * l * ghk ;
   }
 _current += ica;

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
  cai = _ion_cai;
  cao = _ion_cao;
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ double _dica;
  _dica = ica;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_dicadv += (_dica - ica)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ica += ica ;
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
  cai = _ion_cai;
  cao = _ion_cao;
 {   states(_p, _ppvar, _thread, _nt);
  } }}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = n_columnindex;  _dlist1[0] = Dn_columnindex;
 _slist1[1] = l_columnindex;  _dlist1[1] = Dl_columnindex;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "Cav3_3.mod";
static const char* nmodl_file_text = 
  "TITLE CaV 3.3 CA3 hippocampal neuron\n"
  "\n"
  "COMMENT\n"
  "    Cell model: CA3 hippocampal neuron\n"
  "    \n"
  "    Created by jun xu @ Clancy Lab of Cornell University Medical College on 3/27/05\n"
  "    \n"
  "    Geometry: single-compartment model modified on 04/19/07 \n"
  "    Xu J, Clancy CE (2008) Ionic mechanisms of endogenous bursting in CA3 hippocampal pyramidal neurons: \n"
  "        a model study. PLoS ONE 3:e2056- [PubMed]\n"
  "\n"
  "ENDCOMMENT \n"
  " \n"
  " \n"
  " NEURON	{\n"
  "        : CaT--alpha 1I CaV3.3\n"
  "	SUFFIX Cav3_3\n"
  "	USEION ca READ cai, cao WRITE ica\n"
  "	RANGE gCav3_3bar, pcabar, ica, tau_l, tau_n, n_inf, l_inf\n"
  "}\n"
  "\n"
  "UNITS	{\n"
  "	(S) = (siemens)\n"
  "	(mV) = (millivolt)\n"
  "	(mA) = (milliamp)\n"
  "}\n"
  "\n"
  "PARAMETER	{\n"
  "    gCav3_3bar = 0.00001 (S/cm2)\n"
  "    vhalfn = -41.5  :mv\n"
  "    vhalfl = -69.8\n"
  "    kn = 6.2\n"
  "    kl = -6.1\n"
  "    q10 = 2.3\n"
  "    pcabar = 0.0001 : cm/s to check!!!\n"
  "    z= 2\n"
  "    F = 96520 : Farady constant (coulomb/mol)\n"
  "    R = 8.3134 : gas constant (J/K.mol)\n"
  "    PI = 3.14    \n"
  "}\n"
  "\n"
  "ASSIGNED	{\n"
  "	v	(mV)\n"
  "	ica	(mA/cm2)\n"
  "	gCav3_3	(S/cm2)\n"
  "	n_inf\n"
  "	tau_n\n"
  "	l_inf\n"
  "	tau_l\n"
  "	cai     (mM)\n"
  "	cao     (mM)\n"
  "	qt \n"
  "	T  : absolute temperature (K)\n"
  "	ghk\n"
  "	w\n"
  "}\n"
  "\n"
  "STATE	{ \n"
  "	n\n"
  "	l\n"
  "}\n"
  "\n"
  "BREAKPOINT	{\n"
  "    SOLVE states METHOD cnexp\n"
  "    ica = gCav3_3bar*pcabar*n*n*l*ghk\n"
  "}\n"
  "\n"
  "DERIVATIVE states	{\n"
  "	rates()\n"
  "	n' = (n_inf-n)/tau_n\n"
  "	l' = (l_inf-l)/tau_l\n"
  "    }\n"
  "    \n"
  "INITIAL{\n"
  "	T = celsius+273.14\n"
  "	qt = pow(q10,(celsius-28)/10)\n"
  "	rates()\n"
  "	n = n_inf\n"
  "	l = l_inf\n"
  "}\n"
  "\n"
  "PROCEDURE rates(){\n"
  "	n_inf = 1/(1+exp(-(v-vhalfn)/kn))\n"
  "	l_inf = 1/(1+exp(-(v-vhalfl)/kl))\n"
  "	\n"
  "        if (v > -60) {\n"
  "            tau_n = (7.2+0.02*exp(-v/14.7))/qt\n"
  "	    tau_l = (79.5+2.0*exp(-v/9.3))/qt\n"
  "        }else{\n"
  "            tau_n = (0.875*exp((v+120)/41))/qt\n"
  "	    tau_l = 260/qt\n"
  "        }\n"
  "	\n"
  "      w = v*0.001*z*F/(R*T)\n"
  "      ghk = -0.001*z*F*(cao-cai*exp(w))*w/(exp(w)-1)	\n"
  "}\n"
  ;
#endif
