/* Process model C form file: Ip_Switch_Oars.pr.c */
/* Portions of this file copyright 1986-2008 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
const char Ip_Switch_Oars_pr_c [] = "MIL_3_Tfile_Hdr_ 145A 30A modeler 7 60A4762F 60A4762F 1 DESKTOP-L75PK39 ANTL 0 0 none none 0 0 none 0 0 0 0 0 0 0 0 1bcc 1                                                                                                                                                                                                                                                                                                                                                                                                     ";
#include <string.h>



/* OPNET system definitions */
#include <opnet.h>



/* Header Block */

#include "opnet.h"
#include "math.h"



/* 状态转移的宏定义 */
#define  ARRIVAL             (op_intrpt_type () == OPC_INTRPT_STRM)


/*定义包的域*/
#define ID_NO				  0	          
#define  SOUR_GROUP_INDEX      1

#define  SOUR_SWITCH_INDEX     2

#define  SOUR_SERVER_INDEX     3

//可能要添加一项
#define  DEST_GROUP_INDEX      4

#define  DEST_SWITCH_INDEX     5

#define  DEST_SERVER_INDEX     6


 /* 定义不同分组的标记 */

#define PK_DATA_FLAG         0
  





/*定义不同分组的标记*/
#define PATHSETUP_FLAG        0
#define OPTICAL_FLAG          1
#define ACK_FLAG              2

/*输出流的宏定义*/
#define SINK_OUT_STRM         0
#define SG_OUT_STRM           1
#define DG_OUT_STRM           2

/*定义队列的索引*/
#define SUBQ_OP               0 
 



/*函数声明*/
//void ack_arrival_actions(Packet * pkptr);
//void optical_arrival_actions(Packet * pkptr,int instrm);
void electronic_arrival_actions(Packet * pkptr,int instrm);

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
	double	                 		transmission_bandwidth_ele                      ;
	Objid	                  		own_objid                                       ;
	Objid	                  		node_objid                                      ;
	int	                    		local_server_id                                 ;
	double	                 		transmission_bandwidth_opc                      ;
	int	                    		local_group_id                                  ;
	int	                    		local_switch_id                                 ;
	double	                 		packet_data_length                              ;
	double	                 		packet_setup_length                             ;
	} Ip_Switch_Oars_state;

#define transmission_bandwidth_ele		op_sv_ptr->transmission_bandwidth_ele
#define own_objid               		op_sv_ptr->own_objid
#define node_objid              		op_sv_ptr->node_objid
#define local_server_id         		op_sv_ptr->local_server_id
#define transmission_bandwidth_opc		op_sv_ptr->transmission_bandwidth_opc
#define local_group_id          		op_sv_ptr->local_group_id
#define local_switch_id         		op_sv_ptr->local_switch_id
#define packet_data_length      		op_sv_ptr->packet_data_length
#define packet_setup_length     		op_sv_ptr->packet_setup_length

/* These macro definitions will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE
#define FIN_PREAMBLE_DEC	Ip_Switch_Oars_state *op_sv_ptr;
#define FIN_PREAMBLE_CODE	\
		op_sv_ptr = ((Ip_Switch_Oars_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr));


/* Function Block */

#if !defined (VOSD_NO_FIN)
enum { _op_block_origin = __LINE__ + 2};
#endif


/*定义建链分组到达后的处理行为*/
void electronic_arrival_actions(Packet *pkptr, int instrm)
	{
//	Packet *pkptr;
//	int ID_NO_temp;
	
//	int sour_group_temp,sour_switch_temp,sour_server_temp;
	int dest_group_temp,dest_switch_temp,dest_server_temp;
//	double elec_power_temp;
//	int hop_num;
	
    FIN(electronic_arrival_actions(pkptr, instrm));	
/**/		
	if(instrm == 0)  /*从IP核发送，则直接从输出流发送给下一跳节点*/
	
		{    
		
		op_pk_fd_get(pkptr, DEST_GROUP_INDEX, &dest_group_temp);
		op_pk_fd_get(pkptr, DEST_SERVER_INDEX, &dest_server_temp);
		op_pk_fd_get(pkptr, DEST_SWITCH_INDEX, &dest_switch_temp);

		if(local_group_id == dest_group_temp)
		   {
		     if (local_switch_id == dest_switch_temp)
				 op_pk_send_forced(pkptr, SG_OUT_STRM);
			 
			 else if (local_server_id == dest_group_temp)
				 op_pk_send_forced(pkptr, DG_OUT_STRM);
			 
			
			}
		else
			{
	 
				   op_pk_send_forced(pkptr, SG_OUT_STRM);
				  
			 }
		
		
		
		
		
		
		
		}
	else           /*到达目的IP核，记录信息并销毁该建链分组，生成ACK分组，设置相应信息并沿原路返回*/
		{
		/*
		op_pk_fd_get(pkptr,ID_NO,&ID_NO_temp);
		
		op_pk_fd_get(pkptr, SOUR_GROUP_INDEX,  &sour_group_temp);
		
        op_pk_fd_get(pkptr, SOUR_SWITCH_INDEX, &sour_switch_temp);
		
		op_pk_fd_get(pkptr, SOUR_SERVER_INDEX, &sour_server_temp);
	
	    op_pk_fd_get(pkptr, DEST_GROUP_INDEX, &dest_group_temp);
    
		op_pk_fd_get(pkptr, DEST_SWITCH_INDEX, &dest_switch_temp);
		
		op_pk_fd_get(pkptr, DEST_SERVER_INDEX, &dest_server_temp);
		
	//	op_pk_fd_get(pkptr, ELEC_POWER_FIELD, &elec_power_temp);
		
	//	op_pk_fd_get(pkptr, HOP_FIELD, &hop_num );
		*/
		
		op_pk_send_forced(pkptr, SINK_OUT_STRM);
		
		//op_pk_destroy(pkptr);
		
		/*
		pkptr_temp = op_pk_create(ack_length);
		
		op_pk_encap_flag_set(pkptr_temp, ACK_FLAG);
		
	    op_pk_fd_set(pkptr_temp, ID_NO, OPC_FIELD_TYPE_INTEGER, ID_NO_temp, 15);
		 
	    op_pk_fd_set(pkptr_temp, SOUR_ADDR_FIELD_X, OPC_FIELD_TYPE_INTEGER, S_X_temp, 4);
		   
        op_pk_fd_set(pkptr_temp, SOUR_ADDR_FIELD_Y, OPC_FIELD_TYPE_INTEGER, S_Y_temp, 4);
		 
	    op_pk_fd_set(pkptr_temp, SOUR_ADDR_FIELD_Z, OPC_FIELD_TYPE_INTEGER, S_Z_temp, 4);
		
		op_pk_fd_set(pkptr_temp, DEST_ADDR_FIELD_X, OPC_FIELD_TYPE_INTEGER, D_X_temp, 4);
		   
	    op_pk_fd_set(pkptr_temp, DEST_ADDR_FIELD_Y, OPC_FIELD_TYPE_INTEGER, D_Y_temp, 4);
		
		op_pk_fd_set(pkptr_temp, DEST_ADDR_FIELD_Z, OPC_FIELD_TYPE_INTEGER, D_Z_temp, 4);
		
		op_pk_fd_set(pkptr_temp, ELEC_POWER_FIELD, OPC_FIELD_TYPE_DOUBLE, elec_power_temp, 20);
		
		op_pk_fd_set(pkptr_temp, HOP_FIELD, OPC_FIELD_TYPE_INTEGER, hop_num, 5);
		
		*/
		
	//	op_pk_total_size_set(pkptr_temp, ack_length);

			
	//	op_pk_send_forced(pkptr_temp, XMT_OUT_STRM);
	

		
		
		}
	FOUT;
	}









/*定义信息分组到达后的处理行为*/
/*
void optical_arrival_actions(Packet *pkptr, int instrm)
	{
	
	FIN(optical_arrival_actions(pkptr, instrm));
	
	if(instrm == 0)                 /*从IP核发送，则存入队列，等待ACK分组*/
/*		{
		op_subq_pk_insert(SUBQ_OP, pkptr, OPC_QPOS_TAIL);
		}
	else                          /*到达目的IP核，直接发送到sink*/
/*		{
		op_pk_send_forced(pkptr, SINK_OUT_STRM);
		}
	
	FOUT;
	}
*/







/*定义ACK分组到达的处理行为*/
/*void ack_arrival_actions(Packet *pkptr)
	{
	 Packet  *pkptr_optical_temp;
	 double  elec_power_temp;
	 int    hop_num;
	
	
	 FIN(ack_arrival_actions(pkptr));

	  /*得到记录信息*/
/*	  op_pk_fd_get(pkptr, ELEC_POWER_FIELD, &elec_power_temp);
	  op_pk_fd_get(pkptr, HOP_FIELD, &hop_num );
	
      /*把得到的信息写入信息分组，并发送信息分组，然后销毁ACK分组*/
	  
/*      pkptr_optical_temp = op_subq_pk_remove(SUBQ_OP, OPC_QPOS_HEAD);
	  
	  op_pk_fd_set(pkptr_optical_temp, ELEC_POWER_FIELD, OPC_FIELD_TYPE_DOUBLE, elec_power_temp,20);
		
	  op_pk_fd_set(pkptr_optical_temp, HOP_FIELD, OPC_FIELD_TYPE_INTEGER, hop_num, 5);
	  op_pk_send_delayed(pkptr_optical_temp, XMT_OUT_STRM, OP_length/transmission_bandwidth-32/10000000);	

	  op_pk_destroy(pkptr);
	
	
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
	void Ip_Switch_Oars (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Obtype _op_Ip_Switch_Oars_init (int * init_block_ptr);
	void _op_Ip_Switch_Oars_diag (OP_SIM_CONTEXT_ARG_OPT);
	void _op_Ip_Switch_Oars_terminate (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Address _op_Ip_Switch_Oars_alloc (VosT_Obtype, int);
	void _op_Ip_Switch_Oars_svar (void *, const char *, void **);


#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
Ip_Switch_Oars (OP_SIM_CONTEXT_ARG_OPT)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	FIN_MT (Ip_Switch_Oars ());

		{
		/* Temporary Variables */
		Packet * pkptr;
		int instrm;
		/* End of Temporary Variables */


		FSM_ENTER ("Ip_Switch_Oars")

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (init) enter executives **/
			FSM_STATE_ENTER_FORCED_NOLABEL (0, "init", "Ip_Switch_Oars [init enter execs]")
				FSM_PROFILE_SECTION_IN ("Ip_Switch_Oars [init enter execs]", state0_enter_exec)
				{
				/* 得到模块的对象ID*/
				own_objid = op_id_self ();
				/* 得到节点的对象ID   */
				node_objid = op_topo_parent(own_objid);
				
				/*读取节点的属性*/
				op_ima_obj_attr_get(node_objid, "node_group_index", &local_group_id);
				op_ima_obj_attr_get(node_objid, "node_switch_index", &local_switch_id);
				op_ima_obj_attr_get(node_objid, "node_server_index", &local_server_id);
				
				
				
				
				/*读取仿真参数配置*/
				
				op_ima_sim_attr_get (OPC_IMA_DOUBLE, "Setup Packet Length(bits)",&packet_setup_length);
				op_ima_sim_attr_get (OPC_IMA_DOUBLE, "Data Packet Length(bits)", &packet_data_length);
				op_ima_sim_attr_get (OPC_IMA_DOUBLE, "Electrical Transmission Bandwidth(bps)", &transmission_bandwidth_ele);
				op_ima_sim_attr_get (OPC_IMA_DOUBLE, "Optical Transmission Bandwidth(bps)", &transmission_bandwidth_opc);
				
				}
				FSM_PROFILE_SECTION_OUT (state0_enter_exec)

			/** state (init) exit executives **/
			FSM_STATE_EXIT_FORCED (0, "init", "Ip_Switch_Oars [init exit execs]")


			/** state (init) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "init", "idle", "tr_0", "Ip_Switch_Oars [init -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (idle) enter executives **/
			FSM_STATE_ENTER_UNFORCED (1, "idle", state1_enter_exec, "Ip_Switch_Oars [idle enter execs]")

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (3,"Ip_Switch_Oars")


			/** state (idle) exit executives **/
			FSM_STATE_EXIT_UNFORCED (1, "idle", "Ip_Switch_Oars [idle exit execs]")


			/** state (idle) transition processing **/
			FSM_PROFILE_SECTION_IN ("Ip_Switch_Oars [idle trans conditions]", state1_trans_conds)
			FSM_INIT_COND (ARRIVAL)
			FSM_DFLT_COND
			FSM_TEST_LOGIC ("idle")
			FSM_PROFILE_SECTION_OUT (state1_trans_conds)

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 2, state2_enter_exec, ;, "ARRIVAL", "", "idle", "arrival", "tr_1", "Ip_Switch_Oars [idle -> arrival : ARRIVAL / ]")
				FSM_CASE_TRANSIT (1, 1, state1_enter_exec, ;, "default", "", "idle", "idle", "tr_9", "Ip_Switch_Oars [idle -> idle : default / ]")
				}
				/*---------------------------------------------------------*/



			/** state (arrival) enter executives **/
			FSM_STATE_ENTER_FORCED (2, "arrival", state2_enter_exec, "Ip_Switch_Oars [arrival enter execs]")
				FSM_PROFILE_SECTION_IN ("Ip_Switch_Oars [arrival enter execs]", state2_enter_exec)
				{
				 /*得到输入流上的分组*/
				instrm = op_intrpt_strm();
				
				pkptr = op_pk_get(instrm);
				
				
				/*判断分组的标记，调用不同的函数*/
				
				if (op_pk_encap_flag_is_set(pkptr, PK_DATA_FLAG))
					electronic_arrival_actions(pkptr, instrm);
				else
					printf("error! IP Switch\n");
				/*
				else if (op_pk_encap_flag_is_set(pkptr, ACK_FLAG))
					ack_arrival_actions(pkptr);
				 
				else if(op_pk_encap_flag_is_set(pkptr, OPTICAL_FLAG))
					optical_arrival_actions(pkptr,instrm);
				*/
				}
				FSM_PROFILE_SECTION_OUT (state2_enter_exec)

			/** state (arrival) exit executives **/
			FSM_STATE_EXIT_FORCED (2, "arrival", "Ip_Switch_Oars [arrival exit execs]")


			/** state (arrival) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "arrival", "idle", "tr_4", "Ip_Switch_Oars [arrival -> idle : default / ]")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (0,"Ip_Switch_Oars")
		}
	}




void
_op_Ip_Switch_Oars_diag (OP_SIM_CONTEXT_ARG_OPT)
	{
	/* No Diagnostic Block */
	}




void
_op_Ip_Switch_Oars_terminate (OP_SIM_CONTEXT_ARG_OPT)
	{

	FIN_MT (_op_Ip_Switch_Oars_terminate ())


	/* No Termination Block */

	Vos_Poolmem_Dealloc (op_sv_ptr);

	FOUT
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in _op_Ip_Switch_Oars_svar function. */
#undef transmission_bandwidth_ele
#undef own_objid
#undef node_objid
#undef local_server_id
#undef transmission_bandwidth_opc
#undef local_group_id
#undef local_switch_id
#undef packet_data_length
#undef packet_setup_length

#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE

#define FIN_PREAMBLE_DEC
#define FIN_PREAMBLE_CODE

VosT_Obtype
_op_Ip_Switch_Oars_init (int * init_block_ptr)
	{
	VosT_Obtype obtype = OPC_NIL;
	FIN_MT (_op_Ip_Switch_Oars_init (init_block_ptr))

	obtype = Vos_Define_Object_Prstate ("proc state vars (Ip_Switch_Oars)",
		sizeof (Ip_Switch_Oars_state));
	*init_block_ptr = 0;

	FRET (obtype)
	}

VosT_Address
_op_Ip_Switch_Oars_alloc (VosT_Obtype obtype, int init_block)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	Ip_Switch_Oars_state * ptr;
	FIN_MT (_op_Ip_Switch_Oars_alloc (obtype))

	ptr = (Ip_Switch_Oars_state *)Vos_Alloc_Object (obtype);
	if (ptr != OPC_NIL)
		{
		ptr->_op_current_block = init_block;
#if defined (OPD_ALLOW_ODB)
		ptr->_op_current_state = "Ip_Switch_Oars [init enter execs]";
#endif
		}
	FRET ((VosT_Address)ptr)
	}



void
_op_Ip_Switch_Oars_svar (void * gen_ptr, const char * var_name, void ** var_p_ptr)
	{
	Ip_Switch_Oars_state		*prs_ptr;

	FIN_MT (_op_Ip_Switch_Oars_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (void *)OPC_NIL;
		FOUT
		}
	prs_ptr = (Ip_Switch_Oars_state *)gen_ptr;

	if (strcmp ("transmission_bandwidth_ele" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->transmission_bandwidth_ele);
		FOUT
		}
	if (strcmp ("own_objid" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->own_objid);
		FOUT
		}
	if (strcmp ("node_objid" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->node_objid);
		FOUT
		}
	if (strcmp ("local_server_id" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->local_server_id);
		FOUT
		}
	if (strcmp ("transmission_bandwidth_opc" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->transmission_bandwidth_opc);
		FOUT
		}
	if (strcmp ("local_group_id" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->local_group_id);
		FOUT
		}
	if (strcmp ("local_switch_id" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->local_switch_id);
		FOUT
		}
	if (strcmp ("packet_data_length" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->packet_data_length);
		FOUT
		}
	if (strcmp ("packet_setup_length" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->packet_setup_length);
		FOUT
		}
	*var_p_ptr = (void *)OPC_NIL;

	FOUT
	}

