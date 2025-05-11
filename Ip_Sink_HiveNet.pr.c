/* Process model C form file: Ip_Sink_Oars.pr.c */
/* Portions of this file copyright 1986-2008 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
const char Ip_Sink_Oars_pr_c [] = "MIL_3_Tfile_Hdr_ 145A 30A modeler 7 60A4763B 60A4763B 1 DESKTOP-L75PK39 ANTL 0 0 none none 0 0 none 0 0 0 0 0 0 0 0 1bcc 1                                                                                                                                                                                                                                                                                                                                                                                                     ";
#include <string.h>



/* OPNET system definitions */
#include <opnet.h>



/* Header Block */


#include "opnet.h"
#include "math.h"
#include <stdio.h>


/*����״̬ת������*/
#define  ARRIVAL     (op_intrpt_type() == OPC_INTRPT_STRM)
#define  END_SIM     (op_intrpt_type() == OPC_INTRPT_ENDSIM)

#define PK_DATA_FLAG         0
  

/*���岻ͬ����ı��*/
#define PATHSETUP_FLAG        0
#define OPTICAL_FLAG          1
#define ACK_FLAG              2


/*���������*/
#define ID_NO				  0	

#define SOUR_GROUP_INDEX	  1

#define SOUR_SWITCH_INDEX	  2

#define SOUR_SERVER_INDEX	  3
          
#define DEST_GROUP_INDEX      4

#define DEST_SWITCH_INDEX     5

#define DEST_SERVER_INDEX     6



/*  ����ӵİ�����  */
#define ELEC_POWER_FIELD              7                    
#define OPT_POWER_FIELD               8                    
#define OPT_LOSS_FIELD                9                   
#define HOP_FIELD                     10     

/*����ͳ�Ʊ���*/

/*double   total_ete_delay = 0;
long int rvd_pkts = 0;
/*
double Max_Loss_Optic = 0;
long int  Max_Hop_Optic = 0;
double Total_Power_Disspation_Electronic = 0;
double Total_Power_Disspation_Optic  = 0;
double Total_Loss_Optic = 0;
*/

long int rvd_pkts=0; 
double   ete_delay_total = 0;

/*��������*/
static void record_stats();

/* End of Header Block */

#if !defined (VOSD_NO_FIN)
#undef	BIN
#undef	BOUT
#define	BIN		FIN_LOCAL_FIELD(_op_last_line_passed) = __LINE__ - _op_block_origin;
#define	BOUT	BIN
#define	BINIT	FIN_LOCAL_FIELD(_op_last_line_passed) = 0; _op_block_origin = __LINE__;
#else
#define	BINIT
#endif /* #if !defined (VOSD_NO_FIN) */



/* State variable definitions */
typedef struct
	{
	/* Internal state tracking for FSM */
	FSM_SYS_STATE
	/* State Variables */
	Objid	                  		surr_mod_objid                                  ;
	Objid	                  		surr_node_objid                                 ;
	int	                    		END_PER                                         ;
	double	                 		Offered_load                                    ;
	Stathandle	             		ETE_Delay_Vec                                   ;
	Stathandle	             		Throughput_Global_Vec                           ;
	double	                 		packet_data_length                              ;
	double	                 		transmission_bandwidth_ele                      ;
	} Ip_Sink_Oars_state;

#define surr_mod_objid          		op_sv_ptr->surr_mod_objid
#define surr_node_objid         		op_sv_ptr->surr_node_objid
#define END_PER                 		op_sv_ptr->END_PER
#define Offered_load            		op_sv_ptr->Offered_load
#define ETE_Delay_Vec           		op_sv_ptr->ETE_Delay_Vec
#define Throughput_Global_Vec   		op_sv_ptr->Throughput_Global_Vec
#define packet_data_length      		op_sv_ptr->packet_data_length
#define transmission_bandwidth_ele		op_sv_ptr->transmission_bandwidth_ele

/* These macro definitions will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE
#define FIN_PREAMBLE_DEC	Ip_Sink_Oars_state *op_sv_ptr;
#define FIN_PREAMBLE_CODE	\
		op_sv_ptr = ((Ip_Sink_Oars_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr));


/* Function Block */

#if !defined (VOSD_NO_FIN)
enum { _op_block_origin = __LINE__ + 2};
#endif

/*��ͳ����д������ļ�*/
void   record_stats()	  
	{
	FIN(record_stats());
	op_stat_scalar_write("Total Packets Received",    rvd_pkts);
	op_stat_scalar_write("ETE Delay",    ete_delay_total/rvd_pkts);
	/*
	op_stat_scalar_write("ETE Delay(ns)", (double)total_ete_delay/rvd_pkts);
	op_stat_scalar_write("kgc Packet Received", rvd_pkts);
	op_stat_scalar_write("Offered Load", Offered_load);
	op_stat_scalar_write("Average electronic disspation", (double)Total_Power_Disspation_Electronic/rvd_pkts);
	op_stat_scalar_write("Average optic disspation",      (double)Total_Power_Disspation_Optic/rvd_pkts);   
	op_stat_scalar_write("Avetage optic loss",            (double)Total_Loss_Optic/rvd_pkts);
	op_stat_scalar_write("Max optic loss",                (double)Max_Loss_Optic);
	op_stat_scalar_write("Max hop",                       (int)Max_Hop_Optic);
	*/
	printf("�յ��İ�������%d\n",rvd_pkts);
	printf("ETE Delay��%f\n",ete_delay_total/rvd_pkts);
	FOUT;
	}

/* End of Function Block */

/* Undefine optional tracing in FIN/FOUT/FRET */
/* The FSM has its own tracing code and the other */
/* functions should not have any tracing.		  */
#undef FIN_TRACING
#define FIN_TRACING

#undef FOUTRET_TRACING
#define FOUTRET_TRACING

#if defined (__cplusplus)
extern "C" {
#endif
	void Ip_Sink_Oars (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Obtype _op_Ip_Sink_Oars_init (int * init_block_ptr);
	void _op_Ip_Sink_Oars_diag (OP_SIM_CONTEXT_ARG_OPT);
	void _op_Ip_Sink_Oars_terminate (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Address _op_Ip_Sink_Oars_alloc (VosT_Obtype, int);
	void _op_Ip_Sink_Oars_svar (void *, const char *, void **);


#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
Ip_Sink_Oars (OP_SIM_CONTEXT_ARG_OPT)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	FIN_MT (Ip_Sink_Oars ());

		{
		/* Temporary Variables */
		Packet*		pkptr;
		/* ����ͳ�Ʊ��� */
		/*
		double Power_Disspation_Electronic = 0;
		double Power_Disspation_Optic  = 0;
		double Loss_Optic = 0;
		
		int    Hop_Optic = 0;
		*/
		double   ete_delay_temp =0 ;
		/* End of Temporary Variables */


		FSM_ENTER ("Ip_Sink_Oars")

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (init) enter executives **/
			FSM_STATE_ENTER_FORCED_NOLABEL (0, "init", "Ip_Sink_Oars [init enter execs]")
				FSM_PROFILE_SECTION_IN ("Ip_Sink_Oars [init enter execs]", state0_enter_exec)
				{
				/* �õ�ģ��Ķ���ID*/
				surr_mod_objid = op_id_self();
				/* �õ��ڵ�Ķ���ID  */
				surr_node_objid = op_topo_parent(surr_mod_objid);
				
				op_ima_obj_attr_get(surr_node_objid, "Collect_Flag", &END_PER);
				
				
				
				/*    �õ�IP���ܺĵ���ز�����Modelator  �� Detector  �� */
				/*
				op_ima_obj_attr_get(surr_node_objid, "Modulator_Insertion_Loss(dB)",&modulator_loss);
				op_ima_obj_attr_get(surr_node_objid, "Modulator_Power(J/bit)",      &modulator_pow);
				op_ima_obj_attr_get(surr_node_objid, "Modulator_Rate(Gbps)",        &modulator_rate);
				op_ima_obj_attr_get(surr_node_objid, "Detector_Power(J/bit)",       &detector_pow);
				op_ima_obj_attr_get(surr_node_objid, "Detector_Sensitivity(dBm)",   &detector_sen);
				op_ima_obj_attr_get(surr_node_objid, "Detector_Loss(dB)",           &detector_loss);
				op_ima_obj_attr_get(surr_node_objid, "Detector_Rate(Gbps)", &detector_rate);
				*/
				
				ETE_Delay_Vec = op_stat_reg("ETE_Delay_vec(us)", OPC_STAT_INDEX_NONE,OPC_STAT_GLOBAL); 
				Throughput_Global_Vec = op_stat_reg("Through_Global(bps)",OPC_STAT_INDEX_NONE,OPC_STAT_GLOBAL);
				
				
				op_ima_sim_attr_get (OPC_IMA_DOUBLE, "Data Packet Length(bits)", &packet_data_length);
				op_ima_sim_attr_get (OPC_IMA_DOUBLE, "Electrical Transmission Bandwidth(bps)", &transmission_bandwidth_ele);
				op_ima_sim_attr_get(OPC_IMA_DOUBLE, "Offered Load", &Offered_load);
				//op_ima_sim_attr_get(OPC_IMA_DOUBLE, "Optical Fixed Packet Length(bit)", &OP_length);
				
				
				}
				FSM_PROFILE_SECTION_OUT (state0_enter_exec)

			/** state (init) exit executives **/
			FSM_STATE_EXIT_FORCED (0, "init", "Ip_Sink_Oars [init exit execs]")


			/** state (init) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "init", "idle", "tr_0", "Ip_Sink_Oars [init -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (idle) enter executives **/
			FSM_STATE_ENTER_UNFORCED (1, "idle", state1_enter_exec, "Ip_Sink_Oars [idle enter execs]")

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (3,"Ip_Sink_Oars")


			/** state (idle) exit executives **/
			FSM_STATE_EXIT_UNFORCED (1, "idle", "Ip_Sink_Oars [idle exit execs]")


			/** state (idle) transition processing **/
			FSM_PROFILE_SECTION_IN ("Ip_Sink_Oars [idle trans conditions]", state1_trans_conds)
			FSM_INIT_COND (ARRIVAL)
			FSM_TEST_COND (END_SIM)
			FSM_DFLT_COND
			FSM_TEST_LOGIC ("idle")
			FSM_PROFILE_SECTION_OUT (state1_trans_conds)

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 2, state2_enter_exec, ;, "ARRIVAL", "", "idle", "pk_destroy", "tr_3", "Ip_Sink_Oars [idle -> pk_destroy : ARRIVAL / ]")
				FSM_CASE_TRANSIT (1, 3, state3_enter_exec, ;, "END_SIM", "", "idle", "stati_collect", "tr_5", "Ip_Sink_Oars [idle -> stati_collect : END_SIM / ]")
				FSM_CASE_TRANSIT (2, 1, state1_enter_exec, ;, "default", "", "idle", "idle", "tr_6", "Ip_Sink_Oars [idle -> idle : default / ]")
				}
				/*---------------------------------------------------------*/



			/** state (pk_destroy) enter executives **/
			FSM_STATE_ENTER_FORCED (2, "pk_destroy", state2_enter_exec, "Ip_Sink_Oars [pk_destroy enter execs]")
				FSM_PROFILE_SECTION_IN ("Ip_Sink_Oars [pk_destroy enter execs]", state2_enter_exec)
				{
				/*����Ϣ�������ͳ�ƣ�����¼����*/
				pkptr = op_pk_get(op_intrpt_strm()); 
				rvd_pkts++;
				ete_delay_temp = op_sim_time()-op_pk_creation_time_get(pkptr);
				ete_delay_total += op_sim_time()-op_pk_creation_time_get(pkptr);
				//printf("simtime: %f, cretime: %f\n", op_sim_time(),op_pk_creation_time_get(pkptr));
				/*
				
				if (op_pk_encap_flag_is_set(pkptr, OPTICAL_FLAG))
					{
					 op_pk_fd_get(pkptr, ELEC_POWER_FIELD, &Power_Disspation_Electronic);
					 op_pk_fd_get(pkptr, OPT_POWER_FIELD,  &Power_Disspation_Optic);
					 op_pk_fd_get(pkptr, OPT_LOSS_FIELD, &Loss_Optic);
					 Loss_Optic = Loss_Optic + modulator_loss + detector_loss;
				     Power_Disspation_Optic = Power_Disspation_Optic + modulator_pow * OP_length + detector_pow * OP_length;
				
					 op_pk_fd_get(pkptr, HOP_FIELD, &Hop_Optic);
				 
					 Total_Power_Disspation_Electronic += Power_Disspation_Electronic;
					 Total_Power_Disspation_Optic += Power_Disspation_Optic;
					 Total_Loss_Optic += Loss_Optic;
					 if (Max_Loss_Optic < Loss_Optic)	  /*��������*/	 
				 /*        {
						  Max_Loss_Optic = Loss_Optic;
						  }
					 if(Max_Hop_Optic < Hop_Optic)
					 
					     {
						  Max_Hop_Optic = Hop_Optic;
						  
						  }                     
						
					      
					     total_ete_delay += op_sim_time() - op_pk_creation_time_get(pkptr) + OP_length/detector_rate;// 81.92 
					
					     rvd_pkts++;
				
					}
				 */
				op_stat_write(ETE_Delay_Vec, ete_delay_total/rvd_pkts);
				
				op_stat_write(Throughput_Global_Vec, packet_data_length);
				//printf("%f\n", Throughput_Global_Vec);
					
				op_stat_write(Throughput_Global_Vec, 0);
				
				
				/*���������Ϣ����*/
				op_pk_destroy (pkptr);
				}
				FSM_PROFILE_SECTION_OUT (state2_enter_exec)

			/** state (pk_destroy) exit executives **/
			FSM_STATE_EXIT_FORCED (2, "pk_destroy", "Ip_Sink_Oars [pk_destroy exit execs]")


			/** state (pk_destroy) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "pk_destroy", "idle", "tr_4", "Ip_Sink_Oars [pk_destroy -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (stati_collect) enter executives **/
			FSM_STATE_ENTER_UNFORCED (3, "stati_collect", state3_enter_exec, "Ip_Sink_Oars [stati_collect enter execs]")
				FSM_PROFILE_SECTION_IN ("Ip_Sink_Oars [stati_collect enter execs]", state3_enter_exec)
				{
				if (END_PER == 1)
					record_stats();
				
				
				}
				FSM_PROFILE_SECTION_OUT (state3_enter_exec)

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (7,"Ip_Sink_Oars")


			/** state (stati_collect) exit executives **/
			FSM_STATE_EXIT_UNFORCED (3, "stati_collect", "Ip_Sink_Oars [stati_collect exit execs]")


			/** state (stati_collect) transition processing **/
			FSM_TRANSIT_MISSING ("stati_collect")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (0,"Ip_Sink_Oars")
		}
	}




void
_op_Ip_Sink_Oars_diag (OP_SIM_CONTEXT_ARG_OPT)
	{
	/* No Diagnostic Block */
	}




void
_op_Ip_Sink_Oars_terminate (OP_SIM_CONTEXT_ARG_OPT)
	{

	FIN_MT (_op_Ip_Sink_Oars_terminate ())


	/* No Termination Block */

	Vos_Poolmem_Dealloc (op_sv_ptr);

	FOUT
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in _op_Ip_Sink_Oars_svar function. */
#undef surr_mod_objid
#undef surr_node_objid
#undef END_PER
#undef Offered_load
#undef ETE_Delay_Vec
#undef Throughput_Global_Vec
#undef packet_data_length
#undef transmission_bandwidth_ele

#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE

#define FIN_PREAMBLE_DEC
#define FIN_PREAMBLE_CODE

VosT_Obtype
_op_Ip_Sink_Oars_init (int * init_block_ptr)
	{
	VosT_Obtype obtype = OPC_NIL;
	FIN_MT (_op_Ip_Sink_Oars_init (init_block_ptr))

	obtype = Vos_Define_Object_Prstate ("proc state vars (Ip_Sink_Oars)",
		sizeof (Ip_Sink_Oars_state));
	*init_block_ptr = 0;

	FRET (obtype)
	}

VosT_Address
_op_Ip_Sink_Oars_alloc (VosT_Obtype obtype, int init_block)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	Ip_Sink_Oars_state * ptr;
	FIN_MT (_op_Ip_Sink_Oars_alloc (obtype))

	ptr = (Ip_Sink_Oars_state *)Vos_Alloc_Object (obtype);
	if (ptr != OPC_NIL)
		{
		ptr->_op_current_block = init_block;
#if defined (OPD_ALLOW_ODB)
		ptr->_op_current_state = "Ip_Sink_Oars [init enter execs]";
#endif
		}
	FRET ((VosT_Address)ptr)
	}



void
_op_Ip_Sink_Oars_svar (void * gen_ptr, const char * var_name, void ** var_p_ptr)
	{
	Ip_Sink_Oars_state		*prs_ptr;

	FIN_MT (_op_Ip_Sink_Oars_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (void *)OPC_NIL;
		FOUT
		}
	prs_ptr = (Ip_Sink_Oars_state *)gen_ptr;

	if (strcmp ("surr_mod_objid" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->surr_mod_objid);
		FOUT
		}
	if (strcmp ("surr_node_objid" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->surr_node_objid);
		FOUT
		}
	if (strcmp ("END_PER" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->END_PER);
		FOUT
		}
	if (strcmp ("Offered_load" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->Offered_load);
		FOUT
		}
	if (strcmp ("ETE_Delay_Vec" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->ETE_Delay_Vec);
		FOUT
		}
	if (strcmp ("Throughput_Global_Vec" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->Throughput_Global_Vec);
		FOUT
		}
	if (strcmp ("packet_data_length" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->packet_data_length);
		FOUT
		}
	if (strcmp ("transmission_bandwidth_ele" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->transmission_bandwidth_ele);
		FOUT
		}
	*var_p_ptr = (void *)OPC_NIL;

	FOUT
	}

