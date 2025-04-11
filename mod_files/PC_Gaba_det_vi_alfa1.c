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
 
#define nrn_init _nrn_init__PC_gaba_alpha1
#define _nrn_initial _nrn_initial__PC_gaba_alpha1
#define nrn_cur _nrn_cur__PC_gaba_alpha1
#define _nrn_current _nrn_current__PC_gaba_alpha1
#define nrn_jacob _nrn_jacob__PC_gaba_alpha1
#define nrn_state _nrn_state__PC_gaba_alpha1
#define _net_receive _net_receive__PC_gaba_alpha1 
#define kstates kstates__PC_gaba_alpha1 
 
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
#define syntype _p[0]
#define syntype_columnindex 0
#define gmax_factor _p[1]
#define gmax_factor_columnindex 1
#define gmaxA1 _p[2]
#define gmaxA1_columnindex 2
#define Q10_diff _p[3]
#define Q10_diff_columnindex 3
#define Q10_channel _p[4]
#define Q10_channel_columnindex 4
#define Cdur _p[5]
#define Cdur_columnindex 5
#define kon _p[6]
#define kon_columnindex 6
#define koff _p[7]
#define koff_columnindex 7
#define d3 _p[8]
#define d3_columnindex 8
#define r3 _p[9]
#define r3_columnindex 9
#define d1d2 _p[10]
#define d1d2_columnindex 10
#define r1r2 _p[11]
#define r1r2_columnindex 11
#define a1 _p[12]
#define a1_columnindex 12
#define b1 _p[13]
#define b1_columnindex 13
#define a2 _p[14]
#define a2_columnindex 14
#define b2 _p[15]
#define b2_columnindex 15
#define r1 _p[16]
#define r1_columnindex 16
#define r2 _p[17]
#define r2_columnindex 17
#define d1 _p[18]
#define d1_columnindex 18
#define d2 _p[19]
#define d2_columnindex 19
#define Erev _p[20]
#define Erev_columnindex 20
#define tau_1 _p[21]
#define tau_1_columnindex 21
#define tau_rec _p[22]
#define tau_rec_columnindex 22
#define tau_facil _p[23]
#define tau_facil_columnindex 23
#define U _p[24]
#define U_columnindex 24
#define Tmax _p[25]
#define Tmax_columnindex 25
#define onSET _p[26]
#define onSET_columnindex 26
#define M _p[27]
#define M_columnindex 27
#define Rd _p[28]
#define Rd_columnindex 28
#define Diff _p[29]
#define Diff_columnindex 29
#define lamd _p[30]
#define lamd_columnindex 30
#define diff_flag _p[31]
#define diff_flag_columnindex 31
#define nd _p[32]
#define nd_columnindex 32
#define i _p[33]
#define i_columnindex 33
#define ic _p[34]
#define ic_columnindex 34
#define g _p[35]
#define g_columnindex 35
#define gA1 _p[36]
#define gA1_columnindex 36
#define Open _p[37]
#define Open_columnindex 37
#define diffus _p[38]
#define diffus_columnindex 38
#define T _p[39]
#define T_columnindex 39
#define Trelease _p[40]
#define Trelease_columnindex 40
#define xout _p[41]
#define xout_columnindex 41
#define yout _p[42]
#define yout_columnindex 42
#define zout _p[43]
#define zout_columnindex 43
#define uout _p[44]
#define uout_columnindex 44
#define C _p[45]
#define C_columnindex 45
#define CA1 _p[46]
#define CA1_columnindex 46
#define CA2 _p[47]
#define CA2_columnindex 47
#define DA1 _p[48]
#define DA1_columnindex 48
#define DA2 _p[49]
#define DA2_columnindex 49
#define DA2f _p[50]
#define DA2f_columnindex 50
#define OA1 _p[51]
#define OA1_columnindex 51
#define OA2 _p[52]
#define OA2_columnindex 52
#define Mres _p[53]
#define Mres_columnindex 53
#define tpre _p[54]
#define tpre_columnindex 54
#define tspike (_p + 55)
#define tspike_columnindex 55
#define PRE (_p + 155)
#define PRE_columnindex 155
#define numpulses _p[255]
#define numpulses_columnindex 255
#define tzero _p[256]
#define tzero_columnindex 256
#define gbar_Q10 _p[257]
#define gbar_Q10_columnindex 257
#define Q10 _p[258]
#define Q10_columnindex 258
#define DC _p[259]
#define DC_columnindex 259
#define DCA1 _p[260]
#define DCA1_columnindex 260
#define DCA2 _p[261]
#define DCA2_columnindex 261
#define DDA1 _p[262]
#define DDA1_columnindex 262
#define DDA2 _p[263]
#define DDA2_columnindex 263
#define DDA2f _p[264]
#define DDA2f_columnindex 264
#define DOA1 _p[265]
#define DOA1_columnindex 265
#define DOA2 _p[266]
#define DOA2_columnindex 266
#define v _p[267]
#define v_columnindex 267
#define _g _p[268]
#define _g_columnindex 268
#define _tsav _p[269]
#define _tsav_columnindex 269
#define _nd_area  *_ppvar[0]._pval
 
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
 static double _hoc_diffusione(void*);
 static double _hoc_imax(void*);
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

 extern Prop* nrn_point_prop_;
 static int _pointtype;
 static void* _hoc_create_pnt(Object* _ho) { void* create_point_process(int, Object*);
 return create_point_process(_pointtype, _ho);
}
 static void _hoc_destroy_pnt(void*);
 static double _hoc_loc_pnt(void* _vptr) {double loc_point_process(int, void*);
 return loc_point_process(_pointtype, _vptr);
}
 static double _hoc_has_loc(void* _vptr) {double has_loc_point(void*);
 return has_loc_point(_vptr);
}
 static double _hoc_get_loc_pnt(void* _vptr) {
 double get_loc_point_process(void*); return (get_loc_point_process(_vptr));
}
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _extcall_prop = _prop;
 }
 static void _hoc_setdata(void* _vptr) { Prop* _prop;
 _prop = ((Point_process*)_vptr)->_prop;
   _setdata(_prop);
 }
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 0,0
};
 static Member_func _member_func[] = {
 "loc", _hoc_loc_pnt,
 "has_loc", _hoc_has_loc,
 "get_loc", _hoc_get_loc_pnt,
 "diffusione", _hoc_diffusione,
 "imax", _hoc_imax,
 0, 0
};
#define diffusione diffusione_PC_gaba_alpha1
#define imax imax_PC_gaba_alpha1
 extern double diffusione( _threadargsproto_ );
 extern double imax( _threadargsprotocomma_ double , double );
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "U", 0, 1,
 "tau_facil", 0, 1e+09,
 "tau_rec", 1e-09, 1e+09,
 "tau_1", 1e-09, 1e+09,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gmaxA1", "pS",
 "Cdur", "ms",
 "kon", "/ms/mM",
 "koff", "/ms",
 "d3", "/ms",
 "r3", "/ms",
 "d1d2", "/ms/mM",
 "r1r2", "/ms",
 "a1", "/ms",
 "b1", "/ms",
 "a2", "/ms",
 "b2", "/ms",
 "r1", "/ms",
 "r2", "/ms",
 "d1", "/ms",
 "d2", "/ms",
 "Erev", "mV",
 "tau_1", "ms",
 "tau_rec", "ms",
 "tau_facil", "ms",
 "Tmax", "mM",
 "Rd", "um",
 "Diff", "um2/ms",
 "lamd", "nm",
 "i", "nA",
 "ic", "nA",
 "g", "pS",
 "gA1", "nA",
 "T", "mM",
 "Trelease", "mM",
 0,0
};
 static double CA20 = 0;
 static double CA10 = 0;
 static double C0 = 0;
 static double DA2f0 = 0;
 static double DA20 = 0;
 static double DA10 = 0;
 static double OA20 = 0;
 static double OA10 = 0;
 static double delta_t = 0.01;
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
 static void _hoc_destroy_pnt(void* _vptr) {
   destroy_point_process(_vptr);
}
 
static int _ode_count(int);
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(NrnThread*, _Memb_list*, int);
static void _ode_matsol(NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[3]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"PC_gaba_alpha1",
 "syntype",
 "gmax_factor",
 "gmaxA1",
 "Q10_diff",
 "Q10_channel",
 "Cdur",
 "kon",
 "koff",
 "d3",
 "r3",
 "d1d2",
 "r1r2",
 "a1",
 "b1",
 "a2",
 "b2",
 "r1",
 "r2",
 "d1",
 "d2",
 "Erev",
 "tau_1",
 "tau_rec",
 "tau_facil",
 "U",
 "Tmax",
 "onSET",
 "M",
 "Rd",
 "Diff",
 "lamd",
 "diff_flag",
 "nd",
 0,
 "i",
 "ic",
 "g",
 "gA1",
 "Open",
 "diffus",
 "T",
 "Trelease",
 "xout",
 "yout",
 "zout",
 "uout",
 0,
 "C",
 "CA1",
 "CA2",
 "DA1",
 "DA2",
 "DA2f",
 "OA1",
 "OA2",
 0,
 0};
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
  if (nrn_point_prop_) {
	_prop->_alloc_seq = nrn_point_prop_->_alloc_seq;
	_p = nrn_point_prop_->param;
	_ppvar = nrn_point_prop_->dparam;
 }else{
 	_p = nrn_prop_data_alloc(_mechtype, 270, _prop);
 	/*initialize range parameters*/
 	syntype = 0;
 	gmax_factor = 1;
 	gmaxA1 = 918.807;
 	Q10_diff = 1.5;
 	Q10_channel = 2.4;
 	Cdur = 0.3;
 	kon = 20;
 	koff = 2;
 	d3 = 15;
 	r3 = 0.15;
 	d1d2 = 15;
 	r1r2 = 0.007;
 	a1 = 0.06;
 	b1 = 0.03;
 	a2 = 0.4;
 	b2 = 10;
 	r1 = 0.0007;
 	r2 = 0.006;
 	d1 = 0.00033;
 	d2 = 1.2;
 	Erev = -60;
 	tau_1 = 0.1;
 	tau_rec = 36.169;
 	tau_facil = 58.517;
 	U = 0.35;
 	Tmax = 1;
 	onSET = 1;
 	M = 7.506;
 	Rd = 0.978;
 	Diff = 0.223;
 	lamd = 20;
 	diff_flag = 1;
 	nd = 1;
  }
 	_prop->param = _p;
 	_prop->param_size = 270;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 
#define _tqitem &(_ppvar[2]._pvoid)
 static void _net_receive(Point_process*, double*, double);
 static void _net_init(Point_process*, double*, double);
 static void _thread_cleanup(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _PC_Gaba_det_vi_alfa1_reg() {
	int _vectorized = 1;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init,
	 hoc_nrnpointerindex, 3,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
  _extcall_thread = (Datum*)ecalloc(2, sizeof(Datum));
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 0, _thread_cleanup);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 270, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
  hoc_register_dparam_semantics(_mechtype, 2, "netsend");
  hoc_register_dparam_semantics(_mechtype, 3, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_init[_mechtype] = _net_init;
 pnt_receive_size[_mechtype] = 9;
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 PC_gaba_alpha1 PC_Gaba_det_vi_alfa1.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 
#define PI _nrnunit_PI[_nrnunit_use_legacy_]
static double _nrnunit_PI[2] = {0x1.921fb54442d18p+1, 3.14159}; /* 3.14159265358979312 */
static int _reset;
static char *modelname = "Gaba mod file only for fitting purpose ";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 extern double *_nrn_thread_getelm(SparseObj*, int, int);
 
#define _MATELM1(_row,_col) *(_nrn_thread_getelm(_so, _row + 1, _col + 1))
 
#define _RHS1(_arg) _rhs[_arg+1]
  
#define _linmat1  1
 static int _spth1 = 1;
 static int _cvspth1 = 0;
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[8], _dlist1[8]; static double *_temp1;
 static int kstates();
 
double imax ( _threadargsprotocomma_ double _la , double _lb ) {
   double _limax;
 if ( _la > _lb ) {
     _limax = _la ;
     }
   else {
     _limax = _lb ;
     }
   
return _limax;
 }
 
static double _hoc_imax(void* _vptr) {
 double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   _p = ((Point_process*)_vptr)->_prop->param;
  _ppvar = ((Point_process*)_vptr)->_prop->dparam;
  _thread = _extcall_thread;
  _nt = (NrnThread*)((Point_process*)_vptr)->_vnt;
 _r =  imax ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) );
 return(_r);
}
 
double diffusione ( _threadargsproto_ ) {
   double _ldiffusione;
 double _lDifWave , _li , _lcntc , _lfi , _laaa ;
 _lDifWave = 0.0 ;
   _lcntc = imax ( _threadargscomma_ numpulses - 100.0 , 0.0 ) ;
   {int  _li ;for ( _li = ((int) _lcntc ) ; _li <= ((int) numpulses ) ; _li ++ ) {
     _lfi = fmod ( ((double) _li ) , 100.0 ) ;
     tzero = tspike [ ((int) _lfi ) ] ;
     if ( t > tzero ) {
       _laaa = ( - Rd * Rd / ( 4.0 * Diff * ( t - tzero ) ) ) ;
       if ( fabs ( _laaa ) < 699.0 ) {
         _lDifWave = _lDifWave + PRE [ ((int) _lfi ) ] * Mres * exp ( _laaa ) / ( ( 4.0 * PI * Diff * ( 1e-3 ) * lamd ) * ( t - tzero ) ) ;
         }
       else {
         if ( _laaa > 0.0 ) {
           _lDifWave = _lDifWave + PRE [ ((int) _lfi ) ] * Mres * exp ( 699.0 ) / ( ( 4.0 * PI * Diff * ( 1e-3 ) * lamd ) * ( t - tzero ) ) ;
           }
         else {
           _lDifWave = _lDifWave + PRE [ ((int) _lfi ) ] * Mres * exp ( - 699.0 ) / ( ( 4.0 * PI * Diff * ( 1e-3 ) * lamd ) * ( t - tzero ) ) ;
           }
         }
       }
     } }
   _ldiffusione = _lDifWave ;
   
return _ldiffusione;
 }
 
static double _hoc_diffusione(void* _vptr) {
 double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   _p = ((Point_process*)_vptr)->_prop->param;
  _ppvar = ((Point_process*)_vptr)->_prop->dparam;
  _thread = _extcall_thread;
  _nt = (NrnThread*)((Point_process*)_vptr)->_vnt;
 _r =  diffusione ( _p, _ppvar, _thread, _nt );
 return(_r);
}
 
static int kstates (void* _so, double* _rhs, double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt)
 {int _reset=0;
 {
   double b_flux, f_flux, _term; int _i;
 {int _i; double _dt1 = 1.0/dt;
for(_i=1;_i<8;_i++){
  	_RHS1(_i) = -_dt1*(_p[_slist1[_i]] - _p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
} }
 diffus = diffusione ( _threadargs_ ) ;
   Trelease = T ;
   /* ~ C <-> CA1 ( 2.0 * kon * Trelease * Q10 , koff * Q10 )*/
 f_flux =  2.0 * kon * Trelease * Q10 * C ;
 b_flux =  koff * Q10 * CA1 ;
 _RHS1( 3) -= (f_flux - b_flux);
 _RHS1( 2) += (f_flux - b_flux);
 
 _term =  2.0 * kon * Trelease * Q10 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 2 ,3)  -= _term;
 _term =  koff * Q10 ;
 _MATELM1( 3 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ CA1 <-> CA2 ( kon * Trelease * Q10 , 2.0 * koff * Q10 )*/
 f_flux =  kon * Trelease * Q10 * CA1 ;
 b_flux =  2.0 * koff * Q10 * CA2 ;
 _RHS1( 2) -= (f_flux - b_flux);
 _RHS1( 1) += (f_flux - b_flux);
 
 _term =  kon * Trelease * Q10 ;
 _MATELM1( 2 ,2)  += _term;
 _MATELM1( 1 ,2)  -= _term;
 _term =  2.0 * koff * Q10 ;
 _MATELM1( 2 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
  /* ~ CA2 <-> DA2f ( d3 * Q10 , r3 * Q10 )*/
 f_flux =  d3 * Q10 * CA2 ;
 b_flux =  r3 * Q10 * DA2f ;
 _RHS1( 1) -= (f_flux - b_flux);
 _RHS1( 4) += (f_flux - b_flux);
 
 _term =  d3 * Q10 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 4 ,1)  -= _term;
 _term =  r3 * Q10 ;
 _MATELM1( 1 ,4)  -= _term;
 _MATELM1( 4 ,4)  += _term;
 /*REACTION*/
  /* ~ DA1 <-> DA2 ( d1d2 * Trelease * Q10 , r1r2 * Q10 )*/
 f_flux =  d1d2 * Trelease * Q10 * DA1 ;
 b_flux =  r1r2 * Q10 * DA2 ;
 _RHS1( 6) -= (f_flux - b_flux);
 _RHS1( 5) += (f_flux - b_flux);
 
 _term =  d1d2 * Trelease * Q10 ;
 _MATELM1( 6 ,6)  += _term;
 _MATELM1( 5 ,6)  -= _term;
 _term =  r1r2 * Q10 ;
 _MATELM1( 6 ,5)  -= _term;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
  /* ~ OA1 <-> CA1 ( a1 * Q10 , b1 * Q10 )*/
 f_flux =  a1 * Q10 * OA1 ;
 b_flux =  b1 * Q10 * CA1 ;
 _RHS1( 7) -= (f_flux - b_flux);
 _RHS1( 2) += (f_flux - b_flux);
 
 _term =  a1 * Q10 ;
 _MATELM1( 7 ,7)  += _term;
 _MATELM1( 2 ,7)  -= _term;
 _term =  b1 * Q10 ;
 _MATELM1( 7 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ OA2 <-> CA2 ( a2 * Q10 , b2 * Q10 )*/
 f_flux =  a2 * Q10 * OA2 ;
 b_flux =  b2 * Q10 * CA2 ;
 _RHS1( 1) += (f_flux - b_flux);
 
 _term =  a2 * Q10 ;
 _MATELM1( 1 ,0)  -= _term;
 _term =  b2 * Q10 ;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
  /* ~ DA1 <-> CA1 ( r1 * Q10 , d1 * Q10 )*/
 f_flux =  r1 * Q10 * DA1 ;
 b_flux =  d1 * Q10 * CA1 ;
 _RHS1( 6) -= (f_flux - b_flux);
 _RHS1( 2) += (f_flux - b_flux);
 
 _term =  r1 * Q10 ;
 _MATELM1( 6 ,6)  += _term;
 _MATELM1( 2 ,6)  -= _term;
 _term =  d1 * Q10 ;
 _MATELM1( 6 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ DA2 <-> CA2 ( r2 * Q10 , d2 * Q10 )*/
 f_flux =  r2 * Q10 * DA2 ;
 b_flux =  d2 * Q10 * CA2 ;
 _RHS1( 5) -= (f_flux - b_flux);
 _RHS1( 1) += (f_flux - b_flux);
 
 _term =  r2 * Q10 ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 1 ,5)  -= _term;
 _term =  d2 * Q10 ;
 _MATELM1( 5 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
   /* C + CA1 + CA2 + DA1 + DA2 + DA2f + OA1 + OA2 = 1.0 */
 _RHS1(0) =  1.0;
 _MATELM1(0, 0) = 1;
 _RHS1(0) -= OA2 ;
 _MATELM1(0, 7) = 1;
 _RHS1(0) -= OA1 ;
 _MATELM1(0, 4) = 1;
 _RHS1(0) -= DA2f ;
 _MATELM1(0, 5) = 1;
 _RHS1(0) -= DA2 ;
 _MATELM1(0, 6) = 1;
 _RHS1(0) -= DA1 ;
 _MATELM1(0, 1) = 1;
 _RHS1(0) -= CA2 ;
 _MATELM1(0, 2) = 1;
 _RHS1(0) -= CA1 ;
 _MATELM1(0, 3) = 1;
 _RHS1(0) -= C ;
 /*CONSERVATION*/
   } return _reset;
 }
 
static void _net_receive (Point_process* _pnt, double* _args, double _lflag) 
{  double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   _thread = (Datum*)0; _nt = (NrnThread*)_pnt->_vnt;   _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
  if (_tsav > t){ extern char* hoc_object_name(); hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t;   if (_lflag == 1. ) {*(_tqitem) = 0;}
 {
   double _lfi ;
 if ( onSET ) {
     _args[1] = 0.0 ;
     onSET = 0.0 ;
     }
   if ( _lflag  == 0.0 ) {
     _args[2] = _args[2] + 1.0 ;
     if (  ! _args[1] ) {
       _args[3] = t ;
       tpre = t ;
       _args[1] = 1.0 ;
       _args[6] = _args[6] * exp ( - ( t - _args[8] ) / tau_rec ) ;
       _args[6] = _args[6] + ( _args[5] * ( exp ( - ( t - _args[8] ) / tau_1 ) - exp ( - ( t - _args[8] ) / tau_rec ) ) / ( ( tau_1 / tau_rec ) - 1.0 ) ) ;
       _args[5] = _args[5] * exp ( - ( t - _args[8] ) / tau_1 ) ;
       _args[4] = 1.0 - _args[5] - _args[6] ;
       if ( tau_facil > 0.0 ) {
         _args[7] = _args[7] * exp ( - ( t - _args[8] ) / tau_facil ) ;
         _args[7] = _args[7] + U * ( 1.0 - _args[7] ) ;
         }
       else {
         _args[7] = U ;
         }
       _args[5] = _args[5] + _args[4] * _args[7] ;
       T = Tmax * _args[5] ;
       _lfi = fmod ( numpulses , 100.0 ) ;
       PRE [ ((int) _lfi ) ] = _args[5] ;
       tspike [ ((int) _lfi ) ] = t ;
       numpulses = numpulses + 1.0 ;
       _args[8] = t ;
       }
     net_send ( _tqitem, _args, _pnt, t +  Cdur , _args[2] ) ;
     }
   if ( _lflag  == _args[2] ) {
     T = 0.0 ;
     _args[1] = 0.0 ;
     }
   } }
 
static void _net_init(Point_process* _pnt, double* _args, double _lflag) {
       double* _p = _pnt->_prop->param;
    Datum* _ppvar = _pnt->_prop->dparam;
    Datum* _thread = (Datum*)0;
    NrnThread* _nt = (NrnThread*)_pnt->_vnt;
 _args[4] = 0.0 ;
   _args[5] = 0.0 ;
   _args[6] = 0.0 ;
   _args[7] = 0.0 ;
   xout = _args[4] ;
   yout = _args[5] ;
   zout = _args[6] ;
   uout = _args[7] ;
   _args[8] = t ;
   _args[2] = 1.0 ;
   }
 
/*CVODE ode begin*/
 static int _ode_spec1(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
 {int _i; for(_i=0;_i<8;_i++) _p[_dlist1[_i]] = 0.0;}
 diffus = diffusione ( _threadargs_ ) ;
 Trelease = T ;
 /* ~ C <-> CA1 ( 2.0 * kon * Trelease * Q10 , koff * Q10 )*/
 f_flux =  2.0 * kon * Trelease * Q10 * C ;
 b_flux =  koff * Q10 * CA1 ;
 DC -= (f_flux - b_flux);
 DCA1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ CA1 <-> CA2 ( kon * Trelease * Q10 , 2.0 * koff * Q10 )*/
 f_flux =  kon * Trelease * Q10 * CA1 ;
 b_flux =  2.0 * koff * Q10 * CA2 ;
 DCA1 -= (f_flux - b_flux);
 DCA2 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ CA2 <-> DA2f ( d3 * Q10 , r3 * Q10 )*/
 f_flux =  d3 * Q10 * CA2 ;
 b_flux =  r3 * Q10 * DA2f ;
 DCA2 -= (f_flux - b_flux);
 DDA2f += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ DA1 <-> DA2 ( d1d2 * Trelease * Q10 , r1r2 * Q10 )*/
 f_flux =  d1d2 * Trelease * Q10 * DA1 ;
 b_flux =  r1r2 * Q10 * DA2 ;
 DDA1 -= (f_flux - b_flux);
 DDA2 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ OA1 <-> CA1 ( a1 * Q10 , b1 * Q10 )*/
 f_flux =  a1 * Q10 * OA1 ;
 b_flux =  b1 * Q10 * CA1 ;
 DOA1 -= (f_flux - b_flux);
 DCA1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ OA2 <-> CA2 ( a2 * Q10 , b2 * Q10 )*/
 f_flux =  a2 * Q10 * OA2 ;
 b_flux =  b2 * Q10 * CA2 ;
 DOA2 -= (f_flux - b_flux);
 DCA2 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ DA1 <-> CA1 ( r1 * Q10 , d1 * Q10 )*/
 f_flux =  r1 * Q10 * DA1 ;
 b_flux =  d1 * Q10 * CA1 ;
 DDA1 -= (f_flux - b_flux);
 DCA1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ DA2 <-> CA2 ( r2 * Q10 , d2 * Q10 )*/
 f_flux =  r2 * Q10 * DA2 ;
 b_flux =  d2 * Q10 * CA2 ;
 DDA2 -= (f_flux - b_flux);
 DCA2 += (f_flux - b_flux);
 
 /*REACTION*/
   /* C + CA1 + CA2 + DA1 + DA2 + DA2f + OA1 + OA2 = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE matsol*/
 static int _ode_matsol1(void* _so, double* _rhs, double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
   b_flux = f_flux = 0.;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<8;_i++){
  	_RHS1(_i) = _dt1*(_p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
} }
 diffus = diffusione ( _threadargs_ ) ;
 Trelease = T ;
 /* ~ C <-> CA1 ( 2.0 * kon * Trelease * Q10 , koff * Q10 )*/
 _term =  2.0 * kon * Trelease * Q10 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 2 ,3)  -= _term;
 _term =  koff * Q10 ;
 _MATELM1( 3 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ CA1 <-> CA2 ( kon * Trelease * Q10 , 2.0 * koff * Q10 )*/
 _term =  kon * Trelease * Q10 ;
 _MATELM1( 2 ,2)  += _term;
 _MATELM1( 1 ,2)  -= _term;
 _term =  2.0 * koff * Q10 ;
 _MATELM1( 2 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
  /* ~ CA2 <-> DA2f ( d3 * Q10 , r3 * Q10 )*/
 _term =  d3 * Q10 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 4 ,1)  -= _term;
 _term =  r3 * Q10 ;
 _MATELM1( 1 ,4)  -= _term;
 _MATELM1( 4 ,4)  += _term;
 /*REACTION*/
  /* ~ DA1 <-> DA2 ( d1d2 * Trelease * Q10 , r1r2 * Q10 )*/
 _term =  d1d2 * Trelease * Q10 ;
 _MATELM1( 6 ,6)  += _term;
 _MATELM1( 5 ,6)  -= _term;
 _term =  r1r2 * Q10 ;
 _MATELM1( 6 ,5)  -= _term;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
  /* ~ OA1 <-> CA1 ( a1 * Q10 , b1 * Q10 )*/
 _term =  a1 * Q10 ;
 _MATELM1( 7 ,7)  += _term;
 _MATELM1( 2 ,7)  -= _term;
 _term =  b1 * Q10 ;
 _MATELM1( 7 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ OA2 <-> CA2 ( a2 * Q10 , b2 * Q10 )*/
 _term =  a2 * Q10 ;
 _MATELM1( 0 ,0)  += _term;
 _MATELM1( 1 ,0)  -= _term;
 _term =  b2 * Q10 ;
 _MATELM1( 0 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
  /* ~ DA1 <-> CA1 ( r1 * Q10 , d1 * Q10 )*/
 _term =  r1 * Q10 ;
 _MATELM1( 6 ,6)  += _term;
 _MATELM1( 2 ,6)  -= _term;
 _term =  d1 * Q10 ;
 _MATELM1( 6 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ DA2 <-> CA2 ( r2 * Q10 , d2 * Q10 )*/
 _term =  r2 * Q10 ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 1 ,5)  -= _term;
 _term =  d2 * Q10 ;
 _MATELM1( 5 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
   /* C + CA1 + CA2 + DA1 + DA2 + DA2f + OA1 + OA2 = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE end*/
 
static int _ode_count(int _type){ return 8;}
 
static void _ode_spec(NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
     _ode_spec1 (_p, _ppvar, _thread, _nt);
 }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 8; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _cvode_sparse_thread(&_thread[_cvspth1]._pvoid, 8, _dlist1, _p, _ode_matsol1, _ppvar, _thread, _nt);
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
 _ode_matsol_instance1(_threadargs_);
 }}
 
static void _thread_cleanup(Datum* _thread) {
   _nrn_destroy_sparseobj_thread(_thread[_cvspth1]._pvoid);
   _nrn_destroy_sparseobj_thread(_thread[_spth1]._pvoid);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
  CA2 = CA20;
  CA1 = CA10;
  C = C0;
  DA2f = DA2f0;
  DA2 = DA20;
  DA1 = DA10;
  OA2 = OA20;
  OA1 = OA10;
 {
   C = 1.0 ;
   CA1 = 0.0 ;
   CA2 = 0.0 ;
   DA1 = 0.0 ;
   DA2 = 0.0 ;
   DA2f = 0.0 ;
   OA1 = 0.0 ;
   OA2 = 0.0 ;
   Open = 0.0 ;
   T = 0.0 ;
   gbar_Q10 = pow( Q10_diff , ( ( celsius - 30.0 ) / 10.0 ) ) ;
   Q10 = pow( Q10_channel , ( ( celsius - 30.0 ) / 10.0 ) ) ;
   numpulses = 0.0 ;
   Mres = 1e3 * ( 1e3 * 1e15 / 6.022e23 * M ) ;
   {int  _li ;for ( _li = 1 ; _li <= 100 ; _li ++ ) {
     PRE [ _li - 1 ] = 0.0 ;
     tspike [ _li - 1 ] = 0.0 ;
     } }
   tspike [ 0 ] = 1e12 ;
   if ( tau_1 >= tau_rec ) {
     printf ( "Warning: tau_1 (%g) should never be higher neither equal to tau_rec (%g)!\n" , tau_1 , tau_rec ) ;
     tau_rec = tau_1 + 1e-5 ;
     }
   onSET = 1.0 ;
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
 _tsav = -1e20;
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
 initmodel(_p, _ppvar, _thread, _nt);
}
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   Open = OA1 + OA2 ;
   gA1 = gmaxA1 * gbar_Q10 * Open ;
   g = gA1 * gmax_factor ;
   i = ( 1e-6 ) * g * ( v - Erev ) ;
   ic = i ;
   }
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
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
 	}
 _g = (_g - _rhs)/.001;
 _g *=  1.e2/(_nd_area);
 _rhs *= 1.e2/(_nd_area);
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
 {  sparse_thread(&_thread[_spth1]._pvoid, 8, _slist1, _dlist1, _p, &t, dt, kstates, _linmat1, _ppvar, _thread, _nt);
     if (secondorder) {
    int _i;
    for (_i = 0; _i < 8; ++_i) {
      _p[_slist1[_i]] += dt*_p[_dlist1[_i]];
    }}
 }}}
 dt = _dtsav;
}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = OA2_columnindex;  _dlist1[0] = DOA2_columnindex;
 _slist1[1] = CA2_columnindex;  _dlist1[1] = DCA2_columnindex;
 _slist1[2] = CA1_columnindex;  _dlist1[2] = DCA1_columnindex;
 _slist1[3] = C_columnindex;  _dlist1[3] = DC_columnindex;
 _slist1[4] = DA2f_columnindex;  _dlist1[4] = DDA2f_columnindex;
 _slist1[5] = DA2_columnindex;  _dlist1[5] = DDA2_columnindex;
 _slist1[6] = DA1_columnindex;  _dlist1[6] = DDA1_columnindex;
 _slist1[7] = OA1_columnindex;  _dlist1[7] = DOA1_columnindex;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "PC_Gaba_det_vi_alfa1.mod";
static const char* nmodl_file_text = 
  "TITLE Gaba mod file only for fitting purpose \n"
  "\n"
  "COMMENT\n"
  "Thierry Nieus, unpublished results, please keep reserved.\n"
  "Variables with suffix \"_s\" are meant for single IPSC fit, with suffix \"_2\" for CGP experimental condition\n"
  "	Does not work with variable dt!\n"
  "ENDCOMMENT\n"
  "\n"
  "\n"
  "\n"
  "NEURON {\n"
  "	POINT_PROCESS PC_gaba_alpha1\n"
  "	 \n"
  "	NONSPECIFIC_CURRENT i\n"
  "	RANGE Q10_diff,Q10_channel\n"
  "	RANGE g, ic ,Cdur ,Tmax, Erev\n"
  "	RANGE Open\n"
  "\n"
  "	RANGE kon,koff,d3,r3,d1d2,r1r2,a1,b1,a2,b2,r1,r2,d1,d2\n"
  "\n"
  "	RANGE gmaxA1,onSET	\n"
  "	RANGE gA1\n"
  "\n"
  "	RANGE xout,yout,zout,uout	\n"
  "	\n"
  "	RANGE tau_1,tau_rec,tau_facil,U,T,U_2 \n"
  "	RANGE diff_flag,diff_flag2,M,Rd,Diff,lamd\n"
  "	RANGE nd,diffus ,Trelease, gmax_factor, syntype \n"
  "	RANGE C, CA1, CA2, DA1, DA2, DA2f, OA1, OA2	\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "	(nA) 	= (nanoamp)\n"
  "	(mV) 	= (millivolt)\n"
  "	(umho)  = (micromho)\n"
  "	(mM) 	= (milli/liter)\n"
  "	(pS) 	= (picosiemens)\n"
  "	PI   	= (pi)(1)\n"
  "    }\n"
  "    \n"
  "    \n"
  "    \n"
  "    PARAMETER {\n"
  "	syntype\n"
  "	gmax_factor = 1\n"
  "	: Parametri Postsinaptici\n"
  "	gmaxA1	= 918.807	(pS)	\n"
  "	Q10_diff	= 1.5\n"
  "	Q10_channel	= 2.4\n"
  "	Cdur	= 0.3		(ms)	\n"
  "\n"
  "	: A1 kinetic rates EC50=(around) 20 uM, U=0.35\n"
  "	kon	= 20		(/ms/mM)	: 20\n"
  "	koff	= 2		(/ms) 		 \n"
  "	d3	= 15		(/ms) 	: 15	 \n"
  "	r3	= 0.15		(/ms) 	: 0.15, use 3.75 for slices in the PR model\n"
  "	d1d2	= 15		(/ms/mM) : 15	\n"
  "	r1r2	= 0.007		(/ms)	: 0.007\n"
  "	a1	= 0.06		(/ms)	: 0.06\n"
  "	b1	= 0.03		(/ms)\n"
  "	a2	= 0.4		(/ms)	: 0.4\n"
  "	b2	= 10		(/ms)	\n"
  "	r1	= 7e-4		(/ms)\n"
  "	r2	= 6e-3		(/ms)	: 6e-3\n"
  "	d1	= 3.3e-4	(/ms)\n"
  "	d2	= 1.2		(/ms)	: 1.2\n"
  "	\n"
  "	Erev	= -60		(mV)\n"
  "\n"
  "	: Parametri Presinaptici\n"
  "	tau_1 	= 0.1 		(ms) 	< 1e-9, 1e9 >\n"
  "	tau_rec = 36.169 	(ms) 	< 1e-9, 1e9 > 	:43.4\n"
  "	tau_facil = 58.517	(ms) 	< 0, 1e9 >	: 6.22 \n"
  "	U 	= 0.35			< 0, 1 >\n"
  "	 \n"
  "	\n"
  "	Tmax	= 1  		(mM)	\n"
  "	onSET	= 1\n"
  "	 \n"
  "		\n"
  "	: Diffusion parameters\n"
  "	: Diffusion: M=21.500, R=1.033, D=0.223, lamd=0.02 as in excitatory synapses	\n"
  "\n"
  "	M	= 7.506	: numero di (kilo) molecole in una vescicola	(52.76)	\n"
  "	Rd	= 0.978 (um)	:4.79	:4.96	: 4.96 (first fit!)\n"
  "	Diff	= 0.223 (um2/ms)\n"
  "\n"
  "	lamd	= 20 		(nm)\n"
  "	diff_flag	= 1			: flag diffusion on/off\n"
  "	 \n"
  "	nd		= 1			: kernel exponent of diffusion\n"
  "\n"
  "	 \n"
  "	celsius (degC)\n"
  "}\n"
  "\n"
  "\n"
  "ASSIGNED {\n"
  "	v		(mV)		: postsynaptic voltage\n"
  "	i 		(nA)		: current = g*(v - Erev)\n"
  "	ic 		(nA)		: current = g*(v - Erev)\n"
  "	g 		(pS)		: conductance\n"
  "	gA1		(nA)\n"
  "	\n"
  "	Open\n"
  "	diffus	\n"
  " \n"
  "	T		(mM)	\n"
  "	 \n"
  "	Trelease	(mM)\n"
  "	 	\n"
  "	Mres		(mM)	\n"
  "	tpre		(ms)\n"
  "\n"
  "	xout\n"
  "	yout\n"
  "	zout\n"
  "	uout\n"
  "	\n"
  "	tspike[100]	(ms)	: will be initialized by the pointprocess\n"
  "	PRE[100]\n"
  "	:PRE_2[500]\n"
  "	numpulses\n"
  "	tzero\n"
  "	gbar_Q10 (mho/cm2)\n"
  "	Q10 (1)\n"
  "}\n"
  "\n"
  "STATE {	\n"
  "	: CTRL - A1\n"
  "	C\n"
  "	CA1\n"
  "	CA2\n"
  "	DA1\n"
  "	DA2\n"
  "	DA2f\n"
  "	OA1\n"
  "	OA2	\n"
  " \n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	: CTRL - A1\n"
  "	C=1\n"
  "	CA1=0\n"
  "	CA2=0\n"
  "	DA1=0\n"
  "	DA2=0\n"
  "	DA2f=0\n"
  "	OA1=0  	\n"
  "	OA2=0\n"
  "\n"
  " \n"
  "	Open=0\n"
  "	  \n"
  "	T=0 		(mM)\n"
  "	\n"
  "	gbar_Q10 = Q10_diff^((celsius-30)/10)\n"
  "	Q10 = Q10_channel^((celsius-30)/10)\n"
  " \n"
  "	numpulses=0\n"
  "	Mres=1e3* (1e3 * 1e15 / 6.022e23 * M)     : (M) to (mM) so 1e3, 1um^3=1dm^3*1e-15 so 1e15\n"
  "	FROM i=1 TO 100 { PRE[i-1]=0 tspike[i-1]=0 } :PRE_2[500]=0}\n"
  "	tspike[0]=1e12	(ms)\n"
  "	if(tau_1>=tau_rec){ \n"
  "		printf(\"Warning: tau_1 (%g) should never be higher neither equal to tau_rec (%g)!\\n\",tau_1,tau_rec)\n"
  "		tau_rec=tau_1+1e-5\n"
  "		:printf(\"tau_rec has been set to %g\\n\",tau_rec) \n"
  "	} \n"
  "	onSET	= 1\n"
  "	 \n"
  "}\n"
  "	FUNCTION imax(a,b) {\n"
  "	    if (a>b) { imax=a }\n"
  "	    else { imax=b }\n"
  "	}\n"
  "	\n"
  "FUNCTION diffusione(){	 \n"
  "	LOCAL DifWave,i,cntc,fi,aaa\n"
  "	DifWave=0\n"
  "	cntc=imax(numpulses-100,0)\n"
  "	FROM i=cntc  TO numpulses{\n"
  "	    fi=fmod(i,100)\n"
  "	    tzero=tspike[fi]\n"
  "		if(t>tzero){\n"
  "		    aaa = (-Rd*Rd/(4*Diff*(t-tzero)))\n"
  "		    if(fabs(aaa)<699){\n"
  "			DifWave=DifWave+PRE[fi]*Mres*exp(aaa)/((4*PI*Diff*(1e-3)*lamd)*(t-tzero)) : ^nd nd =1\n"
  "		    }else{\n"
  "			if(aaa>0){\n"
  "			    DifWave=DifWave+PRE[fi]*Mres*exp(699)/((4*PI*Diff*(1e-3)*lamd)*(t-tzero)) : ^nd nd =1\n"
  "			}else{\n"
  "			    DifWave=DifWave+PRE[fi]*Mres*exp(-699)/((4*PI*Diff*(1e-3)*lamd)*(t-tzero)) : ^nd nd =1\n"
  "			}\n"
  "		    }\n"
  "		}\n"
  "	}	\n"
  "	diffusione=DifWave\n"
  "}\n"
  "\n"
  "\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE kstates METHOD sparse\n"
  "	\n"
  "	Open=OA1+OA2\n"
  "	\n"
  "	gA1 = gmaxA1 * gbar_Q10 * Open\n"
  "	\n"
  "	g = gA1 * gmax_factor\n"
  "	\n"
  "	i = (1e-6) * g * ( v - Erev )\n"
  "	ic = i\n"
  "}\n"
  "\n"
  "KINETIC kstates {\n"
  "\n"
  "	: ************\n"
  "	: *** CTRL ***	\n"
  "	: ************\n"
  "	\n"
  "\n"
  "	diffus=diffusione() 	\n"
  "	Trelease = T :+ diffus\n"
  "	\n"
  "	:	***	ALFA 1 *** \n"
  "	\n"
  "	: second row\n"
  "	~	C  	<-> 	CA1	(2*kon*Trelease*Q10,koff*Q10)\n"
  "	~	CA1 	<-> 	CA2	(kon*Trelease*Q10,2*koff*Q10)\n"
  "	~	CA2	<->	DA2f	(d3*Q10,r3*Q10)\n"
  "	: third row\n"
  "	~ 	DA1  	<-> 	DA2	(d1d2*Trelease*Q10,r1r2*Q10)\n"
  "	: first <=> second row\n"
  "	~ 	OA1  	<-> 	CA1	(a1*Q10,b1*Q10)\n"
  "	~ 	OA2  	<-> 	CA2	(a2*Q10,b2*Q10)\n"
  "	: third <=> second row\n"
  "	~	DA1	<->	CA1	(r1*Q10,d1*Q10)\n"
  "	~	DA2	<->	CA2	(r2*Q10,d2*Q10)	\n"
  "	CONSERVE C+CA1+CA2+DA1+DA2+DA2f+OA1+OA2=1\n"
  "	\n"
  "}\n"
  "\n"
  "\n"
  "NET_RECEIVE(weight,on, nspike,tzero (ms),x,y,z,u, tsyn (ms)) {LOCAL fi\n"
  "	INITIAL {\n"
  "		x = 0\n"
  "		y = 0\n"
  "		z = 0\n"
  "		u = 0 \n"
  "		 		\n"
  "		xout=x\n"
  "		yout=y\n"
  "		zout=z\n"
  "		uout=u\n"
  "		tsyn = t\n"
  "		nspike = 1\n"
  "	}\n"
  "\n"
  "	if(onSET){\n"
  "		on=0 \n"
  "		onSET=0\n"
  "		 \n"
  "	}\n"
  "	\n"
  "	if (flag == 0) { \n"
  "		: Qui faccio rientrare la modulazione presinaptica\n"
  "		nspike = nspike + 1\n"
  "		:printf(\"T = %g (mM)\\n\",Trelease)\n"
  "		if (!on) {\n"
  "			tzero = t	\n"
  "			tpre=t	: activates diffusion\n"
  "			on = 1		\n"
  "					\n"
  "			z = z*exp(-(t - tsyn)/tau_rec)		\n"
  "			z = z + ( y*(exp(-(t - tsyn)/tau_1) - exp(-(t - tsyn)/tau_rec)) / ((tau_1/tau_rec)-1) )\n"
  "			y = y*exp(-(t - tsyn)/tau_1)			\n"
  "			x = 1-y-z			\n"
  "			if (tau_facil > 0) { \n"
  "				u = u*exp(-(t - tsyn)/tau_facil)\n"
  "				u = u + U * ( 1 - u )							\n"
  "			} else { u = U }\n"
  "			y = y + x * u\n"
  "			T=Tmax*y\n"
  "\n"
  "			 \n"
  "				\n"
  "			fi=fmod(numpulses,100)\n"
  "			PRE[fi]=y	: PRE[numpulses]=y\n"
  "			 \n"
  "			tspike[fi] = t\n"
  "			numpulses=numpulses+1\n"
  "\n"
  "			 \n"
  "\n"
  "			tsyn = t			\n"
  "		}\n"
  "		net_send(Cdur, nspike)\n"
  "		 \n"
  "	}\n"
  "\n"
  "	if (flag == nspike) { \n"
  "		T = 0\n"
  "		 \n"
  "		on = 0\n"
  "	}\n"
  "}\n"
  ;
#endif
