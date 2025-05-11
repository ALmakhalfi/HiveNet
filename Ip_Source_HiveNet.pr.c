/* Process model C form file: Ip_Source_Oars.pr.c */
/* Portions of this file copyright 1986-2008 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
const char Ip_Source_Oars_pr_c [] = "MIL_3_Tfile_Hdr_ 145A 30A modeler 7 60A47636 60A47636 1 DESKTOP-L75PK39 ANTL 0 0 none none 0 0 none 0 0 0 0 0 0 0 0 1bcc 1                                                                                                                                                                                                                                                                                                                                                                                                     ";
#include <string.h>



/* OPNET system definitions */
#include <opnet.h>



/* Header Block */


#include "opnet.h"
#include "math.h"
#include <stdio.h>


/*定义中断码*/
#define	 START			0
#define	 GENERATE			1



/*定义状态转移条件*/
#define     SSC_START             (op_intrpt_code() == START)
#define     END_SIM               (op_intrpt_type() == OPC_INTRPT_ENDSIM)
#define		PACKET_GENERATE	      (op_intrpt_type() == OPC_INTRPT_SELF) && (op_intrpt_code()== GENERATE)



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

                   


/* 定义时间和空间的流量模型 */

#define   UNIFORM_TRAFFIC           1
#define   MATRIX_REVERSE            2
#define   HOTPOT_TRAFFIC_POINT      3
#define   HOTPOT_TRAFFIC_AREA       4
#define   LOCAL_TRAFFIC             5
#define   BIT_REVERSE               6
#define   POINT_TO_POINT_TRAFFIC    7










/*定义不同分组的标识*/
#define PATHSETUP_FLAG        0
#define OPTICAL_FLAG          1
#define ACK_FLAG              2



/*定义统计变量*/
int id_num_global = 0;
long int gen_pkts=0;



/*定义产生目的地址的结构体*/
typedef struct
	{
	
	int  dest_group_gen;
	int  dest_switch_gen ;
	int  dest_server_gen ;
	}FLOW_GEN_INFO;//可能要加一项


/*函数声明*/


static void pk_generate_function();

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
	Objid	                  		own_objid                                       ;
	Objid	                  		node_objid                                      ;
	Evhandle	               		next_pk_evh                                     ;
	double	                 		next_intarr_time                                ;
	double	                 		mean_pk_arrival_time                            ;
	int	                    		send_flag                                       ;
	int	                    		END_PER                                         ;
	double	                 		Offered_load                                    ;
	double	                 		transmission_bandwidth_ele                      ;
	double	                 		transmission_bandwidth_opc                      ;
	int	                    		local_server_id                                 ;
	int	                    		local_group_id                                  ;
	int	                    		local_switch_id                                 ;
	List*	                  		lptr_flow_gen_info                              ;
	double	                 		packet_setup_length                             ;
	double	                 		packet_data_length                              ;
	double	                 		offered_load                                    ;
	Stathandle	             		ETE_Delay_Vec                                   ;
	Stathandle	             		Throughput_Global_Vec                           ;
	} Ip_Source_Oars_state;

#define own_objid               		op_sv_ptr->own_objid
#define node_objid              		op_sv_ptr->node_objid
#define next_pk_evh             		op_sv_ptr->next_pk_evh
#define next_intarr_time        		op_sv_ptr->next_intarr_time
#define mean_pk_arrival_time    		op_sv_ptr->mean_pk_arrival_time
#define send_flag               		op_sv_ptr->send_flag
#define END_PER                 		op_sv_ptr->END_PER
#define Offered_load            		op_sv_ptr->Offered_load
#define transmission_bandwidth_ele		op_sv_ptr->transmission_bandwidth_ele
#define transmission_bandwidth_opc		op_sv_ptr->transmission_bandwidth_opc
#define local_server_id         		op_sv_ptr->local_server_id
#define local_group_id          		op_sv_ptr->local_group_id
#define local_switch_id         		op_sv_ptr->local_switch_id
#define lptr_flow_gen_info      		op_sv_ptr->lptr_flow_gen_info
#define packet_setup_length     		op_sv_ptr->packet_setup_length
#define packet_data_length      		op_sv_ptr->packet_data_length
#define offered_load            		op_sv_ptr->offered_load
#define ETE_Delay_Vec           		op_sv_ptr->ETE_Delay_Vec
#define Throughput_Global_Vec   		op_sv_ptr->Throughput_Global_Vec

/* These macro definitions will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE
#define FIN_PREAMBLE_DEC	Ip_Source_Oars_state *op_sv_ptr;
#define FIN_PREAMBLE_CODE	\
		op_sv_ptr = ((Ip_Source_Oars_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr));


/* Function Block */

#if !defined (VOSD_NO_FIN)
enum { _op_block_origin = __LINE__ + 2};
#endif






static void pk_generate_function()
	{

	Distribution * dest_group_dist = OPC_NIL;
	Distribution * dest_switch_dist = OPC_NIL;
	Distribution * dest_server_dist = OPC_NIL;

	int            dest_group_index =-1;
	int            dest_switch_index =-1;
	int            dest_server_index =-1;
	
	Packet  *pkptr_data_temp= OPC_NIL;
	
	FIN(pk_generate_function())
		
	/*产生目的地址-----均匀流量模型*/
		
		

	dest_group_dist  = op_dist_load ("uniform_int", 0, 3);
	dest_switch_dist = op_dist_load ("uniform_int", 0, 3);
	dest_server_dist = op_dist_load ("uniform_int", 0, 3);
	
	do
		{
		
		dest_group_index  = op_dist_outcome(dest_group_dist);
		dest_switch_index = op_dist_outcome(dest_switch_dist);

		dest_server_index = op_dist_outcome(dest_server_dist);
			
					
		}while(dest_group_index == local_group_id && dest_switch_index == local_switch_id && dest_server_index == local_server_id);//可能加一项
	
	
	/*创建分组，写入相应信息*/
	
	pkptr_data_temp = op_pk_create(packet_data_length);
		
    op_pk_encap_flag_set(pkptr_data_temp ,PK_DATA_FLAG);
		
	op_pk_fd_set (pkptr_data_temp, ID_NO, OPC_FIELD_TYPE_INTEGER, id_num_global, 15);

		
	op_pk_fd_set (pkptr_data_temp, SOUR_GROUP_INDEX, OPC_FIELD_TYPE_INTEGER, local_group_id , 5 );
	
	op_pk_fd_set (pkptr_data_temp, SOUR_SWITCH_INDEX, OPC_FIELD_TYPE_INTEGER, local_switch_id , 5 );
	
	op_pk_fd_set (pkptr_data_temp, SOUR_SERVER_INDEX, OPC_FIELD_TYPE_INTEGER, local_server_id , 5 );
	

	
	op_pk_fd_set (pkptr_data_temp, DEST_GROUP_INDEX,OPC_FIELD_TYPE_INTEGER, dest_group_index,5);
	
	op_pk_fd_set (pkptr_data_temp, DEST_SWITCH_INDEX,OPC_FIELD_TYPE_INTEGER, dest_switch_index,5);
	
	op_pk_fd_set (pkptr_data_temp, DEST_SERVER_INDEX,OPC_FIELD_TYPE_INTEGER, dest_server_index,5);
	
   
	
	op_pk_total_size_set (pkptr_data_temp, packet_data_length);
	
	
	op_pk_send(pkptr_data_temp, 0);
	
	
	 gen_pkts++;
	
	   
	 id_num_global++;
	
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
	void Ip_Source_Oars (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Obtype _op_Ip_Source_Oars_init (int * init_block_ptr);
	void _op_Ip_Source_Oars_diag (OP_SIM_CONTEXT_ARG_OPT);
	void _op_Ip_Source_Oars_terminate (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Address _op_Ip_Source_Oars_alloc (VosT_Obtype, int);
	void _op_Ip_Source_Oars_svar (void *, const char *, void **);


#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
Ip_Source_Oars (OP_SIM_CONTEXT_ARG_OPT)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	FIN_MT (Ip_Source_Oars ());

		{
		/* Temporary Variables */
		//Packet*  pkptr;
		double   ete_delay_temp =0 ;
		//Packet*  pkptr_send ;
		
		int pk_num_temp =0;
		/* End of Temporary Variables */


		FSM_ENTER ("Ip_Source_Oars")

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (init) enter executives **/
			FSM_STATE_ENTER_UNFORCED_NOLABEL (0, "init", "Ip_Source_Oars [init enter execs]")
				FSM_PROFILE_SECTION_IN ("Ip_Source_Oars [init enter execs]", state0_enter_exec)
				{
				/* 得到模块的对象ID*/
				own_objid = op_id_self ();
				/* 得到该节点的对象ID*/
				node_objid = op_topo_parent(own_objid);
				
				
				
				/* 得到该节点的属性*/
				op_ima_obj_attr_get(node_objid, "node_group_index", &local_group_id);
				op_ima_obj_attr_get(node_objid, "node_switch_index", &local_switch_id);
				op_ima_obj_attr_get(node_objid, "node_server_index", &local_server_id);
				op_ima_obj_attr_get(node_objid, "Send Flag", &send_flag);
				op_ima_obj_attr_get(node_objid, "Collect_Flag", &END_PER);
				
				
				
				/*  得到仿真参数配置*/
				
				op_ima_sim_attr_get (OPC_IMA_DOUBLE, "Setup Packet Length(bits)",&packet_setup_length);
				op_ima_sim_attr_get (OPC_IMA_DOUBLE, "Data Packet Length(bits)", &packet_data_length);
				
				
				op_ima_sim_attr_get (OPC_IMA_DOUBLE, "Offered Load(packets/s)", &offered_load);
				op_ima_sim_attr_get (OPC_IMA_DOUBLE, "Electrical Transmission Bandwidth(bps)", &transmission_bandwidth_ele);
				op_ima_sim_attr_get (OPC_IMA_DOUBLE, "Optical Transmission Bandwidth(bps)", &transmission_bandwidth_opc);
				
				//op_ima_sim_attr_get(OPC_IMA_INTEGER, "Node_Traffic_Module", &traffic_module);                  /* 得到IP 流量模型*/
				
				
				/*设置分组的生成间隔*/
				mean_pk_arrival_time  = 1.0/offered_load;
				
				
				lptr_flow_gen_info =op_prg_list_create();
				
				
				
				
				
				/*设置自中断*/
				op_intrpt_schedule_self(op_sim_time (), START);
				}
				FSM_PROFILE_SECTION_OUT (state0_enter_exec)

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (1,"Ip_Source_Oars")


			/** state (init) exit executives **/
			FSM_STATE_EXIT_UNFORCED (0, "init", "Ip_Source_Oars [init exit execs]")


			/** state (init) transition processing **/
			FSM_TRANSIT_ONLY ((SSC_START), 1, state1_enter_exec, ;, init, "SSC_START", "", "init", "pk_generate", "tr_6", "Ip_Source_Oars [init -> pk_generate : SSC_START / ]")
				/*---------------------------------------------------------*/



			/** state (pk_generate) enter executives **/
			FSM_STATE_ENTER_UNFORCED (1, "pk_generate", state1_enter_exec, "Ip_Source_Oars [pk_generate enter execs]")
				FSM_PROFILE_SECTION_IN ("Ip_Source_Oars [pk_generate enter execs]", state1_enter_exec)
				{
				/*分组的产生间隔服从指数分布，设置中断产生分组*/
				if (send_flag == 1)
					{
					pk_generate_function();
				
					next_intarr_time = op_dist_exponential(mean_pk_arrival_time);
				
					next_pk_evh = op_intrpt_schedule_self(op_sim_time () + next_intarr_time, GENERATE);
					
				
					}
				
					
				}
				FSM_PROFILE_SECTION_OUT (state1_enter_exec)

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (3,"Ip_Source_Oars")


			/** state (pk_generate) exit executives **/
			FSM_STATE_EXIT_UNFORCED (1, "pk_generate", "Ip_Source_Oars [pk_generate exit execs]")


			/** state (pk_generate) transition processing **/
			FSM_PROFILE_SECTION_IN ("Ip_Source_Oars [pk_generate trans conditions]", state1_trans_conds)
			FSM_INIT_COND (PACKET_GENERATE)
			FSM_TEST_COND (END_SIM)
			FSM_TEST_LOGIC ("pk_generate")
			FSM_PROFILE_SECTION_OUT (state1_trans_conds)

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 1, state1_enter_exec, ;, "PACKET_GENERATE", "", "pk_generate", "pk_generate", "tr_7", "Ip_Source_Oars [pk_generate -> pk_generate : PACKET_GENERATE / ]")
				FSM_CASE_TRANSIT (1, 2, state2_enter_exec, ;, "END_SIM", "", "pk_generate", "stati_collect", "tr_9", "Ip_Source_Oars [pk_generate -> stati_collect : END_SIM / ]")
				}
				/*---------------------------------------------------------*/



			/** state (stati_collect) enter executives **/
			FSM_STATE_ENTER_UNFORCED (2, "stati_collect", state2_enter_exec, "Ip_Source_Oars [stati_collect enter execs]")
				FSM_PROFILE_SECTION_IN ("Ip_Source_Oars [stati_collect enter execs]", state2_enter_exec)
				{
				/*统计数据*/
				if (op_ev_valid(next_pk_evh) == OPC_TRUE)
					{
					op_ev_cancel(next_pk_evh);	
					}
				
				if(END_PER == 1)
					{
					op_stat_scalar_write("Total Packets Generated",   gen_pkts);
					}
				}
				FSM_PROFILE_SECTION_OUT (state2_enter_exec)

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (5,"Ip_Source_Oars")


			/** state (stati_collect) exit executives **/
			FSM_STATE_EXIT_UNFORCED (2, "stati_collect", "Ip_Source_Oars [stati_collect exit execs]")


			/** state (stati_collect) transition processing **/
			FSM_TRANSIT_MISSING ("stati_collect")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (0,"Ip_Source_Oars")
		}
	}




void
_op_Ip_Source_Oars_diag (OP_SIM_CONTEXT_ARG_OPT)
	{
	/* No Diagnostic Block */
	}




void
_op_Ip_Source_Oars_terminate (OP_SIM_CONTEXT_ARG_OPT)
	{

	FIN_MT (_op_Ip_Source_Oars_terminate ())


	/* No Termination Block */

	Vos_Poolmem_Dealloc (op_sv_ptr);

	FOUT
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in _op_Ip_Source_Oars_svar function. */
#undef own_objid
#undef node_objid
#undef next_pk_evh
#undef next_intarr_time
#undef mean_pk_arrival_time
#undef send_flag
#undef END_PER
#undef Offered_load
#undef transmission_bandwidth_ele
#undef transmission_bandwidth_opc
#undef local_server_id
#undef local_group_id
#undef local_switch_id
#undef lptr_flow_gen_info
#undef packet_setup_length
#undef packet_data_length
#undef offered_load
#undef ETE_Delay_Vec
#undef Throughput_Global_Vec

#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE

#define FIN_PREAMBLE_DEC
#define FIN_PREAMBLE_CODE

VosT_Obtype
_op_Ip_Source_Oars_init (int * init_block_ptr)
	{
	VosT_Obtype obtype = OPC_NIL;
	FIN_MT (_op_Ip_Source_Oars_init (init_block_ptr))

	obtype = Vos_Define_Object_Prstate ("proc state vars (Ip_Source_Oars)",
		sizeof (Ip_Source_Oars_state));
	*init_block_ptr = 0;

	FRET (obtype)
	}

VosT_Address
_op_Ip_Source_Oars_alloc (VosT_Obtype obtype, int init_block)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	Ip_Source_Oars_state * ptr;
	FIN_MT (_op_Ip_Source_Oars_alloc (obtype))

	ptr = (Ip_Source_Oars_state *)Vos_Alloc_Object (obtype);
	if (ptr != OPC_NIL)
		{
		ptr->_op_current_block = init_block;
#if defined (OPD_ALLOW_ODB)
		ptr->_op_current_state = "Ip_Source_Oars [init enter execs]";
#endif
		}
	FRET ((VosT_Address)ptr)
	}



void
_op_Ip_Source_Oars_svar (void * gen_ptr, const char * var_name, void ** var_p_ptr)
	{
	Ip_Source_Oars_state		*prs_ptr;

	FIN_MT (_op_Ip_Source_Oars_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (void *)OPC_NIL;
		FOUT
		}
	prs_ptr = (Ip_Source_Oars_state *)gen_ptr;

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
	if (strcmp ("next_pk_evh" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->next_pk_evh);
		FOUT
		}
	if (strcmp ("next_intarr_time" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->next_intarr_time);
		FOUT
		}
	if (strcmp ("mean_pk_arrival_time" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->mean_pk_arrival_time);
		FOUT
		}
	if (strcmp ("send_flag" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->send_flag);
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
	if (strcmp ("transmission_bandwidth_ele" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->transmission_bandwidth_ele);
		FOUT
		}
	if (strcmp ("transmission_bandwidth_opc" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->transmission_bandwidth_opc);
		FOUT
		}
	if (strcmp ("local_server_id" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->local_server_id);
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
	if (strcmp ("lptr_flow_gen_info" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->lptr_flow_gen_info);
		FOUT
		}
	if (strcmp ("packet_setup_length" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->packet_setup_length);
		FOUT
		}
	if (strcmp ("packet_data_length" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->packet_data_length);
		FOUT
		}
	if (strcmp ("offered_load" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->offered_load);
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
	*var_p_ptr = (void *)OPC_NIL;

	FOUT
	}

