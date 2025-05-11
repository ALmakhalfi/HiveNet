/* Process model C form file: Oarst_AWGR_Switch.pr.c */
/* Portions of this file copyright 1986-2008 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
const char Oarst_AWGR_Switch_pr_c [] = "MIL_3_Tfile_Hdr_ 145A 30A op_runsim 7 60A1C30E 60A1C30E 1 DESKTOP-L75PK39 ANTL 0 0 none none 0 0 none 0 0 0 0 0 0 0 0 1bcc 1                                                                                                                                                                                                                                                                                                                                                                                                   ";
#include <string.h>



/* OPNET system definitions */
#include <opnet.h>



/* Header Block */

/////////////////////////////////////////
#include "opnet.h"
#include "math.h"
#include <stdio.h>
////////////////////////////////////////////////////////////

# define MOU_FLOW           0
# define ELE_FLOW           1


# define FLOW_HEAD          0
# define FLOW_BODY          1
# define FLOW_TAIL          2

///////////////////////////////////////////////////////////
/*������ֶ��е���ʼ��־ */



///////////////////////////////////////////////////////////////






//////////////////////////////////////////////////////////////
/* �����ж��� */
/*
#define Edg_Elec_Switching              0
#define  Agg_Traffic_Rolling            1
#define  Edg_Elep_Send_Rolling          2
*/

#define  Top_Elec_Switching         0









///////////////////////////////////////////////////////////////
/*����״̬ת�Ƶ�����*/
/*
# define     PK_ARRIVAL             (op_intrpt_type()==OPC_INTRPT_STRM)
# define     EDG_ELEC_SWITCH        (op_intrpt_type() == OPC_INTRPT_SELF) &&(op_intrpt_code()== Edg_Elec_Switching)
# define     AGG_TRAFFIC_ROLLING    (op_intrpt_type() == OPC_INTRPT_SELF) &&(op_intrpt_code()== Agg_Traffic_Rolling )
# define     EDG_ELEP_SEND_ROLLING  (op_intrpt_type() == OPC_INTRPT_SELF) &&(op_intrpt_code()==Edg_Elep_Send_Rolling)

*/

# define PK_ARRIVAL (op_intrpt_type() == OPC_INTRPT_STRM)

# define TOP_ELEC_SWITCH (op_intrpt_type() == OPC_INTRPT_SELF) &&(op_intrpt_code()== Top_Elec_Switching)
# define END_SIM (op_intrpt_type() == OPC_INTRPT_ENDSIM)






//////////////////////////////////////////////////////////////
/*���������*/
/*���������*/
#define ID_NO				  0	

#define  SOUR_GROUP_INDEX      1
#define  SOUR_SWITCH_INDEX     2
#define  SOUR_SERVER_INDEX     3


#define  DEST_GROUP_INDEX      4
#define  DEST_SWITCH_INDEX     5
#define  DEST_SERVER_INDEX     6



////////////////////////////////
/* ���岻ͬ����ı�� */

#define PK_DATA_FLAG          0
#define OPC_SETUP_FLAG        1
#define OPC_ACK_FLAG          2
#define OPC_NACK_FLAG         3
#define OPC_ELEP_FLAG         4
#define OPC_TEARDOWN_FLAG     5

/////////////////////////////////////////////////////////////
/*����ȫ�ֱ��� */
//long int elep_flow_num_global =0;

//////////////////////////////////////////////////////////
/*����ṹ��洢rack�ڽ����Ķ˿� */
typedef struct
	{
	int outstrm_index_elec;
	int instrm_index_elec;
	
	}EPORT_INFO;

typedef struct
	{
	int flow_num_info ;
	int port_out_info ;
	}ROUTE_MOU_FLOW;

typedef struct
	{
	int subq_in_elec ;
	int port_out_elec;
	}CANDI_INFO_ELEC;

/*
typedef struct
	{
	int flow_num_elep;
	
	int subq_elep ;
	int wave_num_elep;
	int path_num_elep;
	
	int dest_pod_elep;
	int dest_switch_elep;
	
	} ELEP_SEND_INFO;

typedef struct
	{
	int flow_num_setup ;
	int rvd_num_setup  ;
	int ack_gen_tag    ;
	
	} RVD_SETUP_INFO ;

*/





//////////////////////////////////////////////////////////////////////////

/*
typedef struct
	{
	int subq_in;
	int port_out;
	}LOCAL_CANDI_INFO;



typedef struct
	{
	int opc_flow_num_rec;
	int opc_data_subq_rec;
	int port_out_rec;
	int wave_num_rec;
	}LOCAL_SETUP_INFO;

typedef struct
	{
	int opc_flow_num_cd;
	int subq_in_cd;
	int port_out_cd;
	int wave_num_cd;
	}EXTER_CANDI_INFO;

typedef struct
	{
	int flow_opc_num_info;
	int port_in_info;
	int port_out_info;
	int wave_num_info;
	}TRACE_INFO;


typedef struct
	{
	int opc_flow_num_s;
	int opc_subq_s;
	int port_out_s;
	int wave_num_s;
	
	int dest_position_s[4];
	int dest_cluster_s;
	
	}LOCAL_OPC_INFO;

/////////////////////////////////////////////////////////
/* �������� */
static void flow_pk_arrival_actions(Packet *pkptr, int instrm);
int packet_based_routing(int dest_group_temp, int dest_switch_temp);

//int flow_based_routing (int flow_num_temp , int flow_pk_position_temp , int dest_pod_temp , int dest_switch_temp);
static void top_elec_routing_computation();
static void top_elec_candidate_chose_to_send (int list_len_candidate , int i);
static void top_elec_candidate_rolling();
static void top_elec_candidate_list_empty();




/////////////////////////////////////////////////////////////




/*
static void elec_pk_arr_actions(Packet *pkptr,int instrm);
static void ack_pk_arr_actions(Packet *pkptr,int instrm);
static void nack_pk_arr_actions(Packet *pkptr , int instrm);
static void elep_pk_arr_actions(Packet *pkptr,int instrm);
static void edg_teardown_pk_arr_actions(Packet* pkptr, int instrm);
static void edg_setup_pk_arr_actions(Packet *pkptr,int instrm);



static void edg_elec_routing_computation();
static void edg_elec_candidate_chose_to_send(int list_len ,int i);
static void edg_elec_candidate_rolling();
static void edg_elec_candidate_list_empty();

static void edg_agg_setup_gen();
static void edg_agg_setup_send();
static void edg_teardown_send();
*/














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
	EPORT_INFO *	           		eport_info                                      ;
	Objid	                  		own_objid                                       ;
	Objid	                  		node_objid                                      ;
	double	                 		packet_setup_length                             ;
	double	                 		packet_data_length                              ;
	double	                 		transmission_bandwidth_ele                      ;
	double	                 		packet_ack_length                               ;
	double	                 		packet_teardown_length                          ;
	int	                    		local_group_id                                  ;
	int	                    		local_switch_id                                 ;
	double	                 		transmission_bandwidth_opc                      ;
	int	                    		port_num                                        ;
	List*	                  		lptr_top_elec_candidate_info[4]                 ;
	List*	                  		lptr_elec_routing_trace_info                    ;
	List*	                  		lptr_top_elec_routing_trace_info                ;
	Stathandle	             		stat_conf_handle                                ;
	int	                    		stat_conf_count                                 ;
	int	                    		local_server_id                                 ;
	} Oarst_AWGR_Switch_state;

#define eport_info              		op_sv_ptr->eport_info
#define own_objid               		op_sv_ptr->own_objid
#define node_objid              		op_sv_ptr->node_objid
#define packet_setup_length     		op_sv_ptr->packet_setup_length
#define packet_data_length      		op_sv_ptr->packet_data_length
#define transmission_bandwidth_ele		op_sv_ptr->transmission_bandwidth_ele
#define packet_ack_length       		op_sv_ptr->packet_ack_length
#define packet_teardown_length  		op_sv_ptr->packet_teardown_length
#define local_group_id          		op_sv_ptr->local_group_id
#define local_switch_id         		op_sv_ptr->local_switch_id
#define transmission_bandwidth_opc		op_sv_ptr->transmission_bandwidth_opc
#define port_num                		op_sv_ptr->port_num
#define lptr_top_elec_candidate_info		op_sv_ptr->lptr_top_elec_candidate_info
#define lptr_elec_routing_trace_info		op_sv_ptr->lptr_elec_routing_trace_info
#define lptr_top_elec_routing_trace_info		op_sv_ptr->lptr_top_elec_routing_trace_info
#define stat_conf_handle        		op_sv_ptr->stat_conf_handle
#define stat_conf_count         		op_sv_ptr->stat_conf_count
#define local_server_id         		op_sv_ptr->local_server_id

/* These macro definitions will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE
#define FIN_PREAMBLE_DEC	Oarst_AWGR_Switch_state *op_sv_ptr;
#define FIN_PREAMBLE_CODE	\
		op_sv_ptr = ((Oarst_AWGR_Switch_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr));


/* Function Block */

#if !defined (VOSD_NO_FIN)
enum { _op_block_origin = __LINE__ + 2};
#endif

/**/
static void flow_pk_arrival_actions(Packet *pkptr, int instrm)
{
int i ;

FIN(flow_pk_arrival_actions());
/* ���鵽��󣬴���k������˿ڵ���Ӧ������ */
for(i=0;i<4 ; i++)//i<8
	{
	//printf("*************000000000000000*************");
	if(eport_info[i].instrm_index_elec == instrm)
		{
		op_subq_pk_insert(i,pkptr, OPC_QPOS_TAIL);
		break;
		}
	
	}
FOUT;
	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* ���ڷ����·�� */

int packet_based_routing(int dest_group_temp)
	{
	
	int port_out = -1 ;
 //  Distribution *port_out_dist ;
	
 //   ROUTE_MOU_FLOW * ptr_route_flow_info ;
 //   int list_len_flow ;
 //   int k;
	
	
	FIN(packet_based_routing())
		

	port_out = dest_group_temp;
	
	
	FRET(port_out);
	
		
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
int flow_based_routing (int flow_num_temp , int flow_pk_position_temp , int dest_pod_temp , int dest_switch_temp)
{
int port_out_flow = 0 ;
Distribution *port_out_dist ;
ROUTE_MOU_FLOW * ptr_route_flow_info ;
int list_len_flow ;
int k;

FIN(flow_based_routing());

if(local_pod_id == port_num)/*��ǰ������Ϊ���Ľ���������·��Ψһȷ�� */
/*
	{
	port_out_flow = dest_pod_temp ;
	}

else /*������Ϊ��۲㽻����*/ 
/*
	{
	 if(dest_pod_temp == local_pod_id)/*�������ķ���Ϊ���з��� ��·��Ψһȷ�� */
/*
		{
		port_out_flow = dest_switch_temp ;
		}
	 else /*������Ϊ���з��򣬳�ͷ���������ѡ·֮�⣬�������������ִ���Ϣѡ· */
/*
		 {
		   if(flow_pk_position_temp == FLOW_HEAD)
			 {
			/*���������������˿� */
/*
			 port_out_dist = op_dist_load("uniform_int", port_num/2, port_num-1);
			 port_out_flow = op_dist_outcome(port_out_dist);
			 op_dist_unload(port_out_dist);
			
			 }
		   else
			   {
			   list_len_flow = op_prg_list_size(lptr_top_elec_routing_trace_info);
			    
			   for(k=0;k<list_len_flow ; k++)
				   {
				   ptr_route_flow_info=(ROUTE_MOU_FLOW*) op_prg_list_access(lptr_top_elec_routing_trace_info,k);
				   
				   if(ptr_route_flow_info->flow_num_info == flow_num_temp)
					   {
					   port_out_flow = ptr_route_flow_info->port_out_info ;
					   break;
					   }
				   
				   }
			   
			   
			   
			   }
		   }
	 
	
	
	 }

FRET(port_out_flow);    

}
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////
static void top_elec_routing_computation()
{
int i ;
Packet* pkptr=OPC_NIL;
//int flow_num_temp ;
//int flow_pk_position_temp ;
//int dest_net_temp;
//int dest_pod_temp;
int dest_group_temp;

//int dest_server_temp ;
int port_out_temp ;

//3.21 CANDI_INFO_ELEC * ptr_candidate_info ;

FIN(top_elec_routing_computation());


for(i=0;i<4 ; i++)//����AWG��8���˿�
	
	{
	if(op_subq_empty(i)==OPC_TRUE)
		{
		continue ;
		}
	else
		{
		pkptr = op_subq_pk_remove(i, OPC_QPOS_HEAD);
	//	op_pk_fd_get(pkptr, FLOW_NO, &flow_num_temp);
	//	op_pk_fd_get(pkptr, FLOW_TAG , &flow_pk_position_temp);
	//	op_pk_fd_get(pkptr, DEST_NET_INDEX ,&dest_net_temp);
	//	op_pk_fd_get(pkptr, DEST_POD_INDEX ,&dest_pod_temp);
	//	op_pk_fd_get(pkptr, DEST_UNIQUE_INDEX ,&dest_unique_temp);
		op_pk_fd_get(pkptr, DEST_GROUP_INDEX ,&dest_group_temp);
	//	op_pk_fd_get(pkptr, SOUR_GROUP_INDEX ,&sour_group_temp);
		
		port_out_temp = packet_based_routing(dest_group_temp);
		
	//	port_out_temp = flow_based_routing(flow_num_temp , flow_pk_position_temp , dest_pod_temp , dest_switch_temp);
		
//3.21		ptr_candidate_info =(CANDI_INFO_ELEC*)op_prg_mem_alloc(sizeof(CANDI_INFO_ELEC));
		
//3.21		ptr_candidate_info -> subq_in_elec = i;
//3.21		ptr_candidate_info -> port_out_elec =port_out_temp ;
		
//3.21		op_prg_list_insert(lptr_top_elec_candidate_info[port_out_temp],ptr_candidate_info, OPC_LISTPOS_TAIL);
		op_pk_send_delayed(pkptr,eport_info[port_out_temp].outstrm_index_elec ,packet_data_length/(3*transmission_bandwidth_opc));//3.21
		
		}
	
	}

FOUT ;

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*���ڷ����ת��*/
/*3.21
static void top_elec_candidate_chose_to_send(int list_len_candidate , int i)
{
Distribution *num_chose_dist;


int num_chose;
int j;

CANDI_INFO_ELEC* ptr_candidate_info ;
//ROUTE_MOU_FLOW*  ptr_routing_info ;

Packet* pkptr=OPC_NIL ;
int subq_in_temp ;
int port_out_temp;

//int flow_num_temp ;
//int pk_position_temp;

//int list_len_routing;
//int k;


FIN(top_elec_candidate_chose_to_send());
3.21*/

/*ͳ�Ʒ�����ͻ�ķ���*/
/*
if(list_len_candidate!=1)
	{
	stat_conf_count = stat_conf_count+(list_len_candidate-1);
	}
*/

/*3.21
num_chose_dist = op_dist_load("uniform_int",1,list_len_candidate-1);
num_chose = op_dist_outcome(num_chose_dist);
j = num_chose-1;

ptr_candidate_info = (CANDI_INFO_ELEC*)op_prg_list_access(lptr_top_elec_candidate_info[i],j);
subq_in_temp = ptr_candidate_info->subq_in_elec;
port_out_temp = ptr_candidate_info->port_out_elec;

pkptr = op_subq_pk_remove(subq_in_temp, OPC_QPOS_HEAD);
3.21*/

/*������·������--����*/
/*3.21

op_pk_send_delayed(pkptr,eport_info[port_out_temp].outstrm_index_elec ,packet_data_length/transmission_bandwidth_ele);

//op_pk_send(pkptr,eport_info[port_out_temp].outstrm_index_elec);

FOUT;


}
3.21*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*������������ת��*/

/*

static void top_elec_candidate_chose_to_send(int list_len_candidate , int i)
{
Distribution *num_chose_dist;


int num_chose;
int j;

CANDI_INFO_ELEC* ptr_candidate_info ;
ROUTE_MOU_FLOW*  ptr_routing_info ;

Packet* pkptr=OPC_NIL ;
int subq_in_temp ;
int port_out_temp;
int flow_num_temp ;
int pk_position_temp;

int list_len_routing;
int k;

FIN(top_elec_candidate_rolling());

/*ͳ�Ʒ�����ͻ�ķ���*/
/*
if(list_len_candidate!=1)
	{
	stat_conf_count = stat_conf_count+(list_len_candidate-1);
	}

num_chose_dist = op_dist_load("uniform_int",1,list_len_candidate-1);
num_chose = op_dist_outcome(num_chose_dist);
j = num_chose-1;

ptr_candidate_info = op_prg_list_access(lptr_top_elec_candidate_info[i],j);
subq_in_temp = ptr_candidate_info->subq_in_elec;
port_out_temp = ptr_candidate_info->port_out_elec;

pkptr = op_subq_pk_remove(subq_in_temp, OPC_QPOS_HEAD);

op_pk_fd_get(pkptr, FLOW_NO, &flow_num_temp);
op_pk_fd_get(pkptr, FLOW_PK_POS ,&pk_position_temp);

if(pk_position_temp == FLOW_HEAD)
	{
	    /* DEBUG */
	   /* printf("\n****************************FLOW HEAD *****************************************\n");
		printf("ADDRESS : (%d,%d,%d,%d)\n",local_net_id ,local_pod_id, local_switch_id,local_unique_id);
		printf("flow num :  %d \n", flow_num_temp);
		printf("port out  : %d\n" , i);
		printf("**********************************TRACE RECORD *********************************\n");*/
	
/*	ptr_routing_info = (ROUTE_MOU_FLOW*)op_prg_mem_alloc(sizeof(ROUTE_MOU_FLOW));
	ptr_routing_info-> flow_num_info = flow_num_temp ;
	ptr_routing_info-> port_out_info = port_out_temp ;
	
	op_prg_list_insert(lptr_top_elec_routing_trace_info, ptr_routing_info, OPC_LISTPOS_TAIL);
	
	}
else if(pk_position_temp == FLOW_TAIL)
	{
	/* ɾ����Ŀ */
/*
	list_len_routing = op_prg_list_size(lptr_top_elec_routing_trace_info);
	for(k=0;k<list_len_routing; k++)
		{
		ptr_routing_info=(ROUTE_MOU_FLOW*)op_prg_list_access(lptr_top_elec_routing_trace_info,k);
		
			if(ptr_routing_info->flow_num_info == flow_num_temp)
				{
				op_prg_list_remove(lptr_top_elec_routing_trace_info,k);
				/*DEBUG*/
		/*printf("\n****************************FLOW TAIL*****************************************\n");
		printf("ADDRESS : (%d,%d,%d,%d)\n",local_net_id ,local_pod_id, local_switch_id,local_unique_id);
		printf("flow num :  %d \n", flow_num_temp);
		printf("port out  : %d\n" , i);
		printf("**********************************TRACE DELET *********************************\n");*/
/*
				
				break;
				}
			
		}
	
	
	}

/*������·������--����*/
/*
op_pk_send_delayed(pkptr,eport_info[port_out_temp].outstrm_index_elec ,packet_data_length/transmission_bandwidth_ele);

//op_pk_send(pkptr,eport_info[port_out_temp].outstrm_index_elec);

FOUT;


}

*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*3.21
static void top_elec_candidate_rolling()
{
int i=0;
int list_len_candidate ;

FIN(top_elec_candidate_rolling());

for(i=0; i<8 ; i++)//����AWG��8�����
   {
	list_len_candidate = op_prg_list_size(lptr_top_elec_candidate_info[i]);
	if(list_len_candidate ==0)
		{
		continue;
		}
	else
		{
		
		top_elec_candidate_chose_to_send(list_len_candidate, i);
		
		
		
		}
	}
FOUT;
}
3.21*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*3.21
static void top_elec_candidate_list_empty()

	{
	int i ;
	
	FIN(top_elec_candidate_list_empty());
	for(i=0;i<8;i++)//����AWG��8���˿�
		{
		op_prg_list_free(lptr_top_elec_candidate_info[i]);
		}
		
	FOUT;
	}
3.21*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                          //
//                                                                                                           //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	



////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                     /////////
/////                                                                  /////////   
//                                                                         //////
///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/*
static void local_pk_optical_send(list_len_send)
{
   int i;
    
   LOCAL_OPC_INFO* ptr_local_opc_send ;
   
   int opc_flow_num_temp = 0;
   int opc_subq_num_temp  = 0;
   int port_out_temp     = 0;
   int wave_num_temp     = 0;
   Packet* pkptr_tear;
   Packet* pkptr_opc ;
   
   
   int* item_del_flow_num = OPC_NIL;
   
   int dest_position_id_t[4]={-1,-1,-1,-1};
   int dest_cluster_id_t    =-1;
   
   int t;
   int* del_flow_num_rec;
   LOCAL_OPC_INFO* ptr_opc_item;
   int list_len_opc;
   int k;
   
   int list_len_del ;
   
   Ici* iciptr = OPC_NIL ;
   
   int ID_num_temp=-1;
 
  
   
   
   FIN(local_pk_optical_send());
   

   
   
   for(i=0;i<list_len_send;i++)
   {
   ptr_local_opc_send =(LOCAL_OPC_INFO*)op_prg_list_access(lptr_local_traffic_send_info,i);
   
   opc_flow_num_temp = ptr_local_opc_send -> opc_flow_num_s ;
   opc_subq_num_temp = ptr_local_opc_send -> opc_subq_s     ;
   port_out_temp     = ptr_local_opc_send -> port_out_s     ;
   wave_num_temp     = ptr_local_opc_send -> wave_num_s     ;
   dest_position_id_t[0] = ptr_local_opc_send-> dest_position_s[0];
   dest_position_id_t[1] = ptr_local_opc_send-> dest_position_s[1];
   dest_position_id_t[2] = ptr_local_opc_send-> dest_position_s[2];
   dest_position_id_t[3] = ptr_local_opc_send-> dest_position_s[3];
   
   dest_cluster_id_t      = ptr_local_opc_send-> dest_cluster_s; 
   
   if(OPC_ST_PORT_LOCK[port_out_temp][wave_num_temp]==1)
	   {
	   continue;
	   }
   else
	   { 
   
           /*�������еķ����Ѿ�������� ��������������飬����������������� TEARDOWN_SUBQ_BEGIN */
       /*
		if(op_subq_empty(opc_subq_num_temp)==OPC_TRUE)
	       {
	         pkptr_tear =op_pk_create(packet_teardown_length);
	   
	         op_pk_encap_flag_set(pkptr_tear, OPC_TEARDOWN_FLAG);
	
	         op_pk_fd_set(pkptr_tear, ID_NO_OPC_FLOW,OPC_FIELD_TYPE_INTEGER, opc_flow_num_temp, 15);
	         op_pk_fd_set(pkptr_tear, WAVE_NUM      ,OPC_FIELD_TYPE_INTEGER,  wave_num_temp   ,   3);
	
	         /*д��Դ��ַ��Ŀ�ĵ�ַ */
	     /*    op_pk_fd_set(pkptr_tear, SOUR_POSITION_ID_0,OPC_FIELD_TYPE_INTEGER,local_position_id[0],2);
	         op_pk_fd_set(pkptr_tear, SOUR_POSITION_ID_1,OPC_FIELD_TYPE_INTEGER,local_position_id[1],2);
	         op_pk_fd_set(pkptr_tear, SOUR_POSITION_ID_2,OPC_FIELD_TYPE_INTEGER,local_position_id[2],2);
	         op_pk_fd_set(pkptr_tear, SOUR_POSITION_ID_3,OPC_FIELD_TYPE_INTEGER,local_position_id[3],2);
	         op_pk_fd_set(pkptr_tear, SOUR_CLUSTER_ID   ,OPC_FIELD_TYPE_INTEGER,local_cluster_id    ,3);
	
	         op_pk_fd_set(pkptr_tear, DEST_POSITION_ID_0,OPC_FIELD_TYPE_INTEGER,dest_position_id_t[0],2);
	         op_pk_fd_set(pkptr_tear, DEST_POSITION_ID_1,OPC_FIELD_TYPE_INTEGER,dest_position_id_t[1],2);
	         op_pk_fd_set(pkptr_tear, DEST_POSITION_ID_2,OPC_FIELD_TYPE_INTEGER,dest_position_id_t[2],2);
	         op_pk_fd_set(pkptr_tear, DEST_POSITION_ID_3,OPC_FIELD_TYPE_INTEGER,dest_position_id_t[3],2);
	
	         op_pk_fd_set(pkptr_tear, DEST_CLUSTER_ID   ,OPC_FIELD_TYPE_INTEGER,dest_cluster_id_t    ,3);
	
	         op_pk_total_size_set(pkptr_tear,packet_teardown_length);
	   
	         op_subq_pk_insert(TEARDOWN_SUBQ_BEGIN, pkptr_tear, OPC_QPOS_TAIL);
			 
			 /*debug*/
			 /*
			 printf("*****************************ATTENTION*********************\n");
			 printf(" TEAR DOWN PACKET GENERATES AT NODE  :(%d,%d%d%d%d)\n",local_cluster_id,local_position_id[3],local_position_id[2],local_position_id[1],local_position_id[0]);
			 printf(" The flow id of the teardown packet: %d\n",opc_flow_num_temp);
			 printf(" op_sim_time(us) : %f\n",op_sim_time()*1000000);
			 printf("************************************************************\n\n");
			 */
	   
	          /* ��¼����Ŀ��λ�ã�׼��ɾ������Ŀ */
			 
	   /*
	         item_del_flow_num = (int*)op_prg_mem_alloc(sizeof(int));
			 *item_del_flow_num = opc_flow_num_temp ;
	         op_prg_list_insert(lptr_item_del_info,item_del_flow_num ,OPC_LISTPOS_TAIL);
	    
			 }
		
   
       
       /*�����в�Ϊ�գ��Ӷ��е�ͷ����ȡ���飬�޸ķ�������ţ����͸÷��飻2����ס����˿� OPC_ST_PORT_LOCK,����ICI��Ϣ������һ����ѯ����֮ǰ��������˿� */
       
		/*else
	        {
	          
	   
	   
	         pkptr_opc = op_subq_pk_remove(opc_subq_num_temp,OPC_QPOS_HEAD);
			 
			 
			 /* debug */
			/* op_pk_fd_get(pkptr_opc,ID_NO, &ID_num_temp);
			 
			 /*
			 printf("****************ATTENTION******************\n");
			 printf(" op_sim_time(us)              : %f    \n",op_sim_time()*1000000);
			 printf(" opc_packet is send from node :(%d,%d%d%d%d)\n", local_cluster_id,local_position_id[3],local_position_id[2],local_position_id[1],local_position_id[0]);
			 printf(" ID NUMBER OF THE OPC PACKET  : %d \n", ID_num_temp);
			 printf(" subq of the opc packet       : %d\n ", opc_subq_num_temp);
			 */
			
			 
			 
			 /*
	   
	         op_pk_encap_flag_set(pkptr_opc, OPC_EXTER_FLAG);
	   
	         op_pk_fd_set(pkptr_opc, ID_NO_OPC_FLOW, OPC_FIELD_TYPE_INTEGER, opc_flow_num_temp ,15);
	   
	         op_pk_send_delayed(pkptr_opc, port_exter_rack[port_out_temp].outstrm_wave_channel[wave_num_temp],packet_data_length/(transmission_bandwidth*10000000));
			 
			 OPC_ST_PORT_LOCK[port_out_temp][wave_num_temp]=1;
			 
			 /* debug */
			// printf(" OPC_ST_PORT_LOCK[%d][%d]=%d\n\n",port_out_temp,wave_num_temp,OPC_ST_PORT_LOCK[port_out_temp][wave_num_temp]);
			 
			 /*�� ICI */
		/*
			 iciptr = op_ici_create("OPC_ST_STATE_FREE");
			 op_ici_attr_set(iciptr,"port_out_free",port_out_temp);
			 op_ici_attr_set(iciptr,"wave_num_free",wave_num_temp);
			 op_ici_install(iciptr);
			 
			 op_intrpt_schedule_self(op_sim_time()+(packet_data_length-0.5)/(transmission_bandwidth*10000000), OPC_Port_Out_State_Free);
			 
			 }
			
		}/*end if OPC_ST_PORT_LOCK[port_out_temp][wave_num_temp]!=1*/
 /* }
   
   
   /* debug */
   /*
   list_len_lts = op_prg_list_size(lptr_item_del_info);
   for(k=0;k<list_len_lts;k++)
	   {
	   list_con_del = (int*)op_prg_list_access(lptr_item_del_info,k);
	   printf("del item : %d\n",*list_con_del);
	   }
   
   list_len_lts = op_prg_list_size(lptr_local_traffic_send_info);
   printf(" DEL Before \n");
   for(k=0;k<list_len_lts;k++)
	   {
	   
	   list_con_opc =(LOCAL_OPC_INFO*)op_prg_list_access(lptr_local_traffic_send_info,k);
	   printf(" flow num of the list :%d\n",list_con_opc->opc_flow_num_s);
	   
	   }
   */
   		
   
         /*���� lptr_item_del_info �м�¼������ɾ�� lptr_local_traffic_send_info �е����� */
   /*       
   list_len_del = op_prg_list_size(lptr_item_del_info);
   
           if(list_len_del != 0)
        	{
	           for(t=0;t<list_len_del;t++)
		       {
	     
		        del_flow_num_rec = (int*)op_prg_list_access(lptr_item_del_info,t);
				list_len_opc = op_prg_list_size(lptr_local_traffic_send_info);
				
				for(k=0;k<list_len_opc;k++)
					{
					
					ptr_opc_item = (LOCAL_OPC_INFO*)op_prg_list_access(lptr_local_traffic_send_info,k);
					if(ptr_opc_item ->opc_flow_num_s == *del_flow_num_rec)
						{
						op_prg_list_remove(lptr_local_traffic_send_info, k);
						break;
						}
					}
		
		        		
		        }
	         }
   
   
           /*��� lptr_item_del_info �е���Ϣ */
   /*
            op_prg_list_free(lptr_item_del_info);
			
  
   FOUT;
	
}


////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////
/* ��ѯ��۶��� ��AGG_QUEUE_SEND_BEGIN ��ʼ����96�����У���ѯ�������Ƿ��Ѿ������������飬����δ�����������飬����Ҫ������������ע�뱾�ؽ����������*/
/*void agg_setup_gen()
{

int i=0;
Packet* pkptr_data;
Packet* pkptr_setup;
int dest_cluster_id;
int dest_position_id_3;
int dest_position_id_2;
int dest_position_id_1;
int dest_position_id_0;
int sour_cluster_id;
int sour_position_id_3;
int sour_position_id_2;
int sour_position_id_1;
int sour_position_id_0;
int wave_allot =-1;
int port_out_setup =-1;
int local_setup_subq_in  = 0;

LOCAL_SETUP_INFO*  ptr_local_setup_info;

FIN(agg_setup_gen());

for(i=AGG_QUEUE_SEND_BEGIN;i<AGG_QUEUE_SEND_BEGIN+96;i++)
	{
	if(op_subq_empty(i)==OPC_TRUE)
		{
		continue;
		}
	else
		{
		if(SETUP_GEN_FLAG[i-AGG_QUEUE_SEND_BEGIN]==0)
			{
			/* ��δ�����������飬�����������鲢��������1����󽫽������������Ӧ�Ķ����� */
/*			pkptr_data = op_subq_pk_access(i, OPC_QPOS_HEAD);
			op_pk_fd_get(pkptr_data,DEST_CLUSTER_ID,& dest_cluster_id);
			op_pk_fd_get(pkptr_data,DEST_POSITION_ID_0,&dest_position_id_0);
			op_pk_fd_get(pkptr_data,DEST_POSITION_ID_1,&dest_position_id_1);
			op_pk_fd_get(pkptr_data,DEST_POSITION_ID_2,&dest_position_id_2);
			op_pk_fd_get(pkptr_data,DEST_POSITION_ID_3,&dest_position_id_3);
			
			op_pk_fd_get(pkptr_data,SOUR_CLUSTER_ID   , &sour_cluster_id);
			op_pk_fd_get(pkptr_data,SOUR_POSITION_ID_0, &sour_position_id_0);
			op_pk_fd_get(pkptr_data,SOUR_POSITION_ID_1, &sour_position_id_1);
			op_pk_fd_get(pkptr_data,SOUR_POSITION_ID_2, &sour_position_id_2);
			op_pk_fd_get(pkptr_data,SOUR_POSITION_ID_3, &sour_position_id_3);
			
			/* ����Դ��ַ�Լ�Ŀ�ĵ�ַȷ��ͨ��ʹ�õĲ������ */
//			wave_allot = wave_allocation(dest_cluster_id,dest_position_id_0,dest_position_id_1,dest_position_id_2,dest_position_id_3,sour_cluster_id ,sour_position_id_0,sour_position_id_1,sour_position_id_2,sour_position_id_3);
			
			
			
			/* ������������ */
			
/*			pkptr_setup = op_pk_create(packet_setup_length);
			
			op_pk_encap_flag_set(pkptr_setup,OPC_SETUP_FLAG);
			
			op_pk_fd_set(pkptr_setup, ID_NO_OPC_FLOW,OPC_FIELD_TYPE_INTEGER, opc_flow_num, 15);
			
			op_pk_fd_set(pkptr_setup, SOUR_POSITION_ID_0,OPC_FIELD_TYPE_INTEGER,sour_position_id_0,2);
			op_pk_fd_set(pkptr_setup, SOUR_POSITION_ID_1,OPC_FIELD_TYPE_INTEGER,sour_position_id_1,2);
			op_pk_fd_set(pkptr_setup, SOUR_POSITION_ID_2,OPC_FIELD_TYPE_INTEGER,sour_position_id_2,2);
			op_pk_fd_set(pkptr_setup, SOUR_POSITION_ID_3,OPC_FIELD_TYPE_INTEGER,sour_position_id_3,2);
			op_pk_fd_set(pkptr_setup, SOUR_CLUSTER_ID,   OPC_FIELD_TYPE_INTEGER,sour_cluster_id,   3);
			
			op_pk_fd_set(pkptr_setup, DEST_POSITION_ID_0,OPC_FIELD_TYPE_INTEGER,dest_position_id_0,2);
			op_pk_fd_set(pkptr_setup, DEST_POSITION_ID_1,OPC_FIELD_TYPE_INTEGER,dest_position_id_1,2);
			op_pk_fd_set(pkptr_setup, DEST_POSITION_ID_2,OPC_FIELD_TYPE_INTEGER,dest_position_id_2,2);
			op_pk_fd_set(pkptr_setup, DEST_POSITION_ID_3,OPC_FIELD_TYPE_INTEGER,dest_position_id_3,2);
			op_pk_fd_set(pkptr_setup, DEST_CLUSTER_ID,   OPC_FIELD_TYPE_INTEGER,dest_cluster_id,   3);
			
			op_pk_fd_set(pkptr_setup, WAVE_NUM          ,OPC_FIELD_TYPE_INTEGER,wave_allot     ,   3);
			
			op_pk_total_size_set(pkptr_setup, packet_setup_length);
			
			/* ����·�ɺ�����������˿� */
//			port_out_setup = setup_routing_computation(dest_position_id_0, dest_position_id_1,dest_position_id_2,dest_position_id_3 ,dest_cluster_id);
						
			/* д����Ϣ��¼�б� */
			
/*			ptr_local_setup_info = (LOCAL_SETUP_INFO*)op_prg_mem_alloc(sizeof(LOCAL_SETUP_INFO));
			
			ptr_local_setup_info->opc_flow_num_rec  = opc_flow_num ;
			ptr_local_setup_info->opc_data_subq_rec = i;
			ptr_local_setup_info->port_out_rec      = port_out_setup;
			ptr_local_setup_info->wave_num_rec      = wave_allot    ;
			op_prg_list_insert(lptr_local_setup_info,ptr_local_setup_info,OPC_LISTPOS_TAIL);
			
				
			/*���������������Ӧ�Ķ����� */
/*		    local_setup_subq_in = LOCAL_SETUP_SEND_BEGIN + port_out_setup*15+wave_allot;
			
			op_subq_pk_insert(local_setup_subq_in,pkptr_setup, OPC_QPOS_TAIL);
			
			/*���������Ϣ*/
			
/*			opc_flow_num++;
			SETUP_GEN_FLAG[i-AGG_QUEUE_SEND_BEGIN]=1;
			
			/*dubug*/
			/*
			printf("***********************************ATTENTION******************************\n");
			printf(" OP_SIM_TIME(us): %f       \n",op_sim_time()*1000000);
			printf(" SETUP Packet generate !\n");
			printf(" LOCAL ADDRESS:(%d,%d%d%d%d) \n", sour_cluster_id,sour_position_id_3,sour_position_id_2,sour_position_id_1,sour_position_id_0);
			printf(" DEST  ADDRESS:(%d,%d%d%d%d) \n", dest_cluster_id,dest_position_id_3,dest_position_id_2,dest_position_id_1,dest_position_id_0);
			printf(" opc_flow_num : %d           \n", opc_flow_num-1);
			printf(" SETUP_GEN_FLAG[%d]: %d      \n", i-AGG_QUEUE_SEND_BEGIN,SETUP_GEN_FLAG[i-AGG_QUEUE_SEND_BEGIN]);
			*/
/*			
			}
		}
	}


FOUT;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void exter_rolling_check()
{
  Packet*  pkptr;
  int      port_out_temp;
  int      dest_pos_id[4]={0,0,0,0};
  int      dest_cluster_id = 0;
  
  int      wave_num_temp           ;
 
   int    flow_num_temp;
  
  EXTER_CANDI_INFO*  ptr_setup_candi_info ;
  
  TRACE_INFO*        ptr_trace_info;
  EXTER_CANDI_INFO*  ptr_ack_candi_info   ;
  
  LOCAL_SETUP_INFO*  ptr_local_trace_info  ;
  
  EXTER_CANDI_INFO*  ptr_tear_candi_info;
  
  
  int     list_len ;
  int     i;
  int     j;
  
 
   
  
	
	/* ��ѯ ��ת�������еĽ������� */
  
/*  FIN(exter_rolling_check());
  
	for(i=SETUP_EXTER_SUBQ_BEGIN;i<SETUP_EXTER_SUBQ_BEGIN+90;i++)
		{
		if(op_subq_empty(i)==OPC_TRUE)
			{
			continue;
			}
		else
			{
			/*
			pkptr=op_subq_pk_access(i,OPC_QPOS_HEAD);
			op_pk_fd_get(pkptr,DEST_POSITION_ID_0,&dest_pos_id[0]);
			op_pk_fd_get(pkptr,DEST_POSITION_ID_1,&dest_pos_id[1]);
			op_pk_fd_get(pkptr,DEST_POSITION_ID_2,&dest_pos_id[2]);
			op_pk_fd_get(pkptr,DEST_POSITION_ID_3,&dest_pos_id[3]);
			
			op_pk_fd_get(pkptr,DEST_CLUSTER_ID   ,&dest_cluster_id);
			
			op_pk_fd_get(pkptr,WAVE_NUM          ,&wave_num_temp  );
			
			op_pk_fd_get(pkptr,ID_NO_OPC_FLOW    ,&flow_num_temp  );
			
			
			
			port_out_temp = setup_routing_computation(dest_pos_id[0],dest_pos_id[1],dest_pos_id[2],dest_pos_id[3],dest_cluster_id);
			
			if(PORT_WAVE_LOCK[port_out_temp][wave_num_temp] !=1)
				{
				/*  ��¼����������Ϣ */
		/*		ptr_setup_candi_info = (EXTER_CANDI_INFO*)op_prg_mem_alloc(sizeof(EXTER_CANDI_INFO));
				ptr_setup_candi_info->opc_flow_num_cd = flow_num_temp;
			    ptr_setup_candi_info->subq_in_cd = i;
				ptr_setup_candi_info->port_out_cd = port_out_temp;
				ptr_setup_candi_info->wave_num_cd = wave_num_temp;
				
				op_prg_list_insert(lptr_exter_setup_candidate_info[port_out_temp],ptr_setup_candi_info,OPC_LISTPOS_TAIL);							
				
				}
						
			
			}
		
		
		} /* �������ڴ�ת�� �����������ѯ */
  
  /*��ѯ���ض˿ڵĽ���������� ��Ϊ���ؽ�������ķ��Ͳ��ü�¼�� lptr_exter_traffic_info �У������������Ϣ����ֻ�ñ�����Ϣ �Ӷ��кţ�����˿ںţ�������*/
/*  for(i=LOCAL_SETUP_SEND_BEGIN;i<LOCAL_SETUP_SEND_BEGIN+90;i++)
	  {
	  if(op_subq_empty(i)==OPC_TRUE)
		  {
		  continue;
		  }
	  else
		  {
		  /*���㱾�ؽ��������Ŀ������˿�  �Լ� ��ԤԼ�Ĳ��� */
	/*	  port_out_temp = (i - LOCAL_SETUP_SEND_BEGIN)/15;
		  wave_num_temp = (i - LOCAL_SETUP_SEND_BEGIN)%15;
		  
		  pkptr=op_subq_pk_access(i,OPC_QPOS_HEAD);
		  
		  op_pk_fd_get(pkptr, ID_NO_OPC_FLOW, &flow_num_temp);
		  
		  
		  /*д�������б� */
	/*	  if(PORT_WAVE_LOCK[port_out_temp][wave_num_temp]!=1)
			  {
			  ptr_setup_candi_info = (EXTER_CANDI_INFO*)op_prg_mem_alloc(sizeof(EXTER_CANDI_INFO));
			  ptr_setup_candi_info -> opc_flow_num_cd = flow_num_temp;
			  ptr_setup_candi_info -> subq_in_cd = i;
			  ptr_setup_candi_info -> port_out_cd = port_out_temp ;
			  ptr_setup_candi_info -> wave_num_cd = wave_num_temp ;
			  
			  op_prg_list_insert(lptr_exter_setup_candidate_info[port_out_temp],ptr_setup_candi_info,OPC_LISTPOS_TAIL);
			  
			  }
		  }
	  
	  }
  
  /*����6������˿ڵ�ack���������ѯ */
/*  for(i=ACK_SUBQ_BEGIN; i<ACK_SUBQ_BEGIN+6;i++)
	  {
	  if(op_subq_empty(i)==OPC_TRUE)
		  {
		  continue;
		  }
	  else
		  {
		  pkptr = op_subq_pk_access(i,OPC_QPOS_HEAD);
		  op_pk_fd_get(pkptr,ID_NO_OPC_FLOW, &flow_num_temp);
		  
		  
		  /*���ټ��б��в�ѯACK���������˿� */
/*		  list_len = op_prg_list_size(lptr_exter_traffic_trace_info);
		  
		  for(j=0;j<list_len;j++)
			  {
			  ptr_trace_info = (TRACE_INFO*)op_prg_list_access(lptr_exter_traffic_trace_info,j);
			  if(ptr_trace_info->flow_opc_num_info == flow_num_temp)
				  {
				  port_out_temp = ptr_trace_info->port_in_info;
				  break;
				  }  
			  
			  }/* ������������˿ڵĲ�ѯ */
		
		  /* д���Ӧ����˿ڵ������б� */
	/*	  ptr_ack_candi_info = (EXTER_CANDI_INFO*)op_prg_mem_alloc(sizeof(EXTER_CANDI_INFO));
		  ptr_ack_candi_info->subq_in_cd = i;
		  ptr_ack_candi_info->port_out_cd= port_out_temp;
		  op_prg_list_insert(lptr_exter_ack_candidate_info[port_out_temp],ptr_ack_candi_info,OPC_LISTPOS_TAIL);
		  }
	  }/* ��������ACK������е���ѯ */
		  
/* ��������ACK�������ѯ���� */
  
/*���ڵȴ�ת���Ĳ�������Ĵ������д洢����BEGIN Ϊ���صĲ���������� ������6�����зֱ�洢����6������Ķ˿��ϵķ��� */
/*  for (i=TEARDOWN_SUBQ_BEGIN;i<TEARDOWN_SUBQ_BEGIN+7;i++)
	  {
	  if(op_subq_empty(i)==OPC_TRUE)
		  {
		  continue;
		  }
	  else
		  {
		  pkptr = op_subq_pk_access(i,OPC_QPOS_HEAD);
		  
		  op_pk_fd_get(pkptr,ID_NO_OPC_FLOW,&flow_num_temp);
		  
		  op_pk_fd_get(pkptr,WAVE_NUM      ,&wave_num_temp);
		  
		  port_out_temp =-1;
		  
		  /*���ڱ��ؽ�������������Ϣ��¼�� lptr_local_setup_info �У�ת�������������Ϣ��¼ ��  lptr_exter_traffic_info ��*/
/*		  if(i==TEARDOWN_SUBQ_BEGIN)
			  {
			  list_len = op_prg_list_size(lptr_local_setup_info);
			  for(j=0;j<list_len;j++)
				 {
				 ptr_local_trace_info = (LOCAL_SETUP_INFO*)op_prg_list_access(lptr_local_setup_info,j);
				 
								 
				 if(ptr_local_trace_info->opc_flow_num_rec == flow_num_temp)
					 {
					 port_out_temp = ptr_local_trace_info->port_out_rec;
					
					 break;
					 }
				 
				 }
		    			  
			  }
		  
		  else
			  {
			  list_len = op_prg_list_size(lptr_exter_traffic_trace_info);
			  for(j=0;j<list_len;j++)
				  {
				  ptr_trace_info = (TRACE_INFO*)op_prg_list_access(lptr_exter_traffic_trace_info,j);
				  
				  if(ptr_trace_info->flow_opc_num_info == flow_num_temp)
					  {
					  port_out_temp = ptr_trace_info-> port_out_info ;
					  break;
					  }
				  }
			  }
		  
		  /*д����Ӧ�˿ڵ������б� lptr_exter_teardown_candidate_info */
/*		  ptr_tear_candi_info = (EXTER_CANDI_INFO*)op_prg_mem_alloc(sizeof(EXTER_CANDI_INFO));
		  
		  ptr_tear_candi_info->opc_flow_num_cd = flow_num_temp;
		  ptr_tear_candi_info->subq_in_cd = i;
		  ptr_tear_candi_info->port_out_cd = port_out_temp;
		  ptr_tear_candi_info->wave_num_cd = wave_num_temp;
		  op_prg_list_insert(lptr_exter_teardown_candidate_info[port_out_temp],ptr_tear_candi_info,OPC_LISTPOS_TAIL);
		  
		  
		  
		  
		  }
	  
	  }/* �������ڲ���������е���ѯ */
  
/*  
FOUT;
	
  }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*ѡ��������鷢�ͣ�����������Ϊ���ز������飺���к�Ϊ TEARDOWN_SUBQ_BEGIN ,��������� ɾ�������б� lptr_local_setup_info �е���Ϣ�� ����ɾ�� lptr_exter_traffic_trace_info �е���Ϣ */
/*void exter_tear_chose_to_send(int list_len_mid,int i)
	{
	int j=-1;
	Distribution* num_chose_dist;
	int       num_chose=-1;
	int list_len_tear;
	
	Packet* pkptr;
	
	EXTER_CANDI_INFO* ptr_candidate_tear_info;

	int subq_in_temp =-1;
	int portout_temp =-1;
	
	int list_len_trace =-1;
	
	LOCAL_SETUP_INFO* ptr_local_trace_info;
	TRACE_INFO*   ptr_exter_trace_info;
	int opc_flow_id_temp;
	
	int wave_num_temp =-1;
	
	int k=-1;
	
	int subq_local_data =-1;
	
	
	FIN(exter_tear_chose_to_send());
	
    list_len_tear = list_len_mid;
	
	num_chose_dist = op_dist_load("uniform_int",1,list_len_tear);
	num_chose  = op_dist_outcome(num_chose_dist);
	op_dist_unload(num_chose_dist);
		
	
    
	j=num_chose -1;
	
	ptr_candidate_tear_info = (EXTER_CANDI_INFO*)op_prg_list_access(lptr_exter_teardown_candidate_info[i],j);
	subq_in_temp= ptr_candidate_tear_info->subq_in_cd;
	portout_temp = ptr_candidate_tear_info->port_out_cd;
	opc_flow_id_temp = ptr_candidate_tear_info->opc_flow_num_cd;
	wave_num_temp = ptr_candidate_tear_info->wave_num_cd;
	
	
	/*��������Ϊ���ز������� , 1 ɾ�� lptr_local_setup_info �е������Ŀ 2 ��������˿ڵĶ�Ӧ���� 3 ������������Ĳ������ SETUP_GEN_FLAG */
	
/*	if(subq_in_temp == TEARDOWN_SUBQ_BEGIN)
		{
		pkptr = op_subq_pk_remove(subq_in_temp,OPC_QPOS_HEAD);
		
		/* ���Ͳ������� */
/*		op_pk_send_delayed(pkptr,port_exter_rack[portout_temp].outstrm_setup_index,packet_teardown_length/(transmission_bandwidth*10000000));
		
		
	    /*1 ɾ���б� lptr_local_setup_info �е������Ϣ 2 ��������˿�   */
	/*	list_len_trace = op_prg_list_size(lptr_local_setup_info);
		
		for(k=0;k<list_len_trace;k++)
			{
			ptr_local_trace_info = (LOCAL_SETUP_INFO*)op_prg_list_access(lptr_local_setup_info,k);
			
			if(ptr_local_trace_info->opc_flow_num_rec == opc_flow_id_temp)
				{
				
				subq_local_data = ptr_local_trace_info->opc_data_subq_rec ;
				
				op_prg_list_remove(lptr_local_setup_info,k);
				break;
				}
			
			}
		PORT_WAVE_LOCK[portout_temp][wave_num_temp] = 0;
		
		SETUP_GEN_FLAG[subq_local_data- AGG_QUEUE_SEND_BEGIN]=0;
		
		/*dubug*/
		/*
	printf("****************************ATTENTION****************************\n");
	printf(" Teardown  PACKET is sent from node (%d,%d%d%d%d)\n",local_cluster_id,local_position_id[3],local_position_id[2],local_position_id[1],local_position_id[0]);
	printf(" op_sim_time(us)  : %f\n",op_sim_time()*1000000);
	printf(" PORT_WAVE_LOCK[%d][%d] = %d \n",portout_temp,wave_num_temp,PORT_WAVE_LOCK[portout_temp][wave_num_temp]);
	printf(" SETUP_GEN_FLAG[%d] = %d\n",subq_local_data- AGG_QUEUE_SEND_BEGIN,SETUP_GEN_FLAG[subq_local_data- AGG_QUEUE_SEND_BEGIN]);
		*/
		
		/*}
	
/*���򣬲�������Ǳ��صĲ������飬1 ��trace ��Ϣ�� lptr_exter_traffic_trace_info ��ɾ�� ; 2 ��������˿ڵĶ�Ӧ���� */

/*	else
		{
		pkptr = op_subq_pk_remove(subq_in_temp,OPC_QPOS_HEAD);
		op_pk_send_delayed(pkptr,port_exter_rack[portout_temp].outstrm_setup_index,packet_teardown_length/(transmission_bandwidth*10000000));
		
		list_len_trace = op_prg_list_size(lptr_exter_traffic_trace_info);
		for(k=0;k<list_len_trace;k++)
		   {
			 ptr_exter_trace_info=(TRACE_INFO*)op_prg_list_access(lptr_exter_traffic_trace_info,k);
		     
		     if(ptr_exter_trace_info->flow_opc_num_info == opc_flow_id_temp)
				 {
				 op_prg_list_remove(lptr_exter_traffic_trace_info,k);
				 break;
				 }
		   }
		PORT_WAVE_LOCK[portout_temp][wave_num_temp]=0;
		/*
		printf("****************************ATTENTION****************************\n");
	    printf(" Teardown  PACKET is sent from node (%d,%d%d%d%d)\n",local_cluster_id,local_position_id[3],local_position_id[2],local_position_id[1],local_position_id[0]);
	    printf(" op_sim_time(us)  : %f\n",op_sim_time()*1000000);
	    printf(" PORT_WAVE_LOCK[%d][%d] = %d \n",portout_temp,wave_num_temp,PORT_WAVE_LOCK[portout_temp][wave_num_temp]);
		*/
/*		           
		}
	FOUT;	
	
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*ѡ����Ӧ���е�ACK���鲢���͸÷��飬�����������Ĵ����� */
/*void exter_ack_chose_to_send(int list_len_mid, int i)
{
int j=-1;
Distribution* num_chose_dist=OPC_NIL;
int num_chose     =-1;

EXTER_CANDI_INFO* ptr_ack_candidate_info;
int list_len;

Packet* pkptr;

FIN(exter_ack_chose_to_send());

list_len = list_len_mid;

num_chose_dist = op_dist_load("uniform_int", 1, list_len);
num_chose      = op_dist_outcome(num_chose_dist);
op_dist_unload(num_chose_dist);

for(j=0;j<list_len;j++)
	{
	if(j==num_chose-1)
		{
		ptr_ack_candidate_info=(EXTER_CANDI_INFO*)op_prg_list_access(lptr_exter_ack_candidate_info[i],j);
		
		/* ���͸ý������� */
		
/*		pkptr=op_subq_pk_remove(ptr_ack_candidate_info->subq_in_cd,OPC_QPOS_HEAD);
		op_pk_send_delayed(pkptr,port_exter_rack[ptr_ack_candidate_info->port_out_cd].outstrm_setup_index, packet_ack_length/(transmission_bandwidth*10000000));
		/*dubug*/
		/*
	printf("****************************ATTENTION****************************\n");
	printf(" ACK  PACKET is sent from node (%d,%d%d%d%d)\n",local_cluster_id,local_position_id[3],local_position_id[2],local_position_id[1],local_position_id[0]);
	printf(" op_sim_time(us)  : %f\n",op_sim_time()*1000000);
		*/
	
/*		break;
		
		}
	}

FOUT;
		
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*���� setup ����Ĵ��� �� 1 ���ͷ��� 2 ��������Ϣд���б� 3 �������˿ڵ���Ӧ����ռ�� */
/*
void exter_setup_chose_to_send(int list_mid , int i)
	{
	int list_len_setup;
	int j=-1;
	Distribution* num_chose_dist ;
	int           num_chose;
          
		
	EXTER_CANDI_INFO* ptr_setup_candidate_info;
	TRACE_INFO*   ptr_setup_trace_info ;
	
	Packet* pkptr;
	
	int opc_flow_num_temp =-1;
	int port_out_temp = -1;
	int port_in_temp =-1;
	int subq_in_temp =-1;
	int wave_num_temp=-1;
	
	FIN(exter_setup_chose_to_send());
	
	list_len_setup = list_mid;
	
	num_chose_dist = op_dist_load("uniform_int", 1, list_len_setup);
	num_chose      = op_dist_outcome(num_chose_dist);
	
	op_dist_unload(num_chose_dist);
	
	j=num_chose-1;
	
	ptr_setup_candidate_info = (EXTER_CANDI_INFO*)op_prg_list_access(lptr_exter_setup_candidate_info[i],j);
	
	opc_flow_num_temp = ptr_setup_candidate_info-> opc_flow_num_cd;
	subq_in_temp      = ptr_setup_candidate_info-> subq_in_cd     ;
	port_out_temp     = ptr_setup_candidate_info-> port_out_cd    ;
	wave_num_temp     = ptr_setup_candidate_info-> wave_num_cd    ;
	
	
	/*���ؽ����������Ϣ��¼�� lptr_local_setup_info �� */
/*	if(subq_in_temp>LOCAL_SETUP_SEND_BEGIN -1 && subq_in_temp <LOCAL_SETUP_SEND_BEGIN+90)
		{
		pkptr = op_subq_pk_remove(subq_in_temp, OPC_QPOS_HEAD);
		
		/* �������˿ڵ� ����ռ��*/
		
/*		PORT_WAVE_LOCK[port_out_temp][wave_num_temp]=1;		
		
		op_pk_send_delayed(pkptr, port_exter_rack[port_out_temp].outstrm_setup_index,packet_setup_length/(transmission_bandwidth*10000000)*2);
		
		/* debug */
		/*
		printf("**********************ATTENTION***********************\n");
	    printf("op_sim_time(us)  : %f\n",op_sim_time()*1000000);
	    printf("setup packet is sent from node (%d,%d%d%d%d) \n",local_cluster_id,local_position_id[3],local_position_id[2],local_position_id[1],local_position_id[0]);
		printf("PORT_WAVE_LOCK[%d][%d]: %d \n",port_out_temp,wave_num_temp,PORT_WAVE_LOCK[port_out_temp][wave_num_temp]);
		*/
		
//		}
	
	/*��ת���������飬��Ҫ��¼��Ϣ���������˿ڵĶ�Ӧ����Ϊռ��״̬*/
	
/*	else
		{
		/* ���ݶ��кż�������˿ں� */
/*		port_in_temp =(subq_in_temp-SETUP_EXTER_SUBQ_BEGIN)/15;
		
		/*����������������Ϣ��¼�� lptr_exter_traffic_trace_info �� */
		
/*		pkptr = op_subq_pk_remove(subq_in_temp,OPC_QPOS_HEAD);
		
		ptr_setup_trace_info=(TRACE_INFO*)op_prg_mem_alloc(sizeof(TRACE_INFO));
		
		ptr_setup_trace_info->flow_opc_num_info = opc_flow_num_temp;
		ptr_setup_trace_info->port_in_info      = port_in_temp     ;
		ptr_setup_trace_info->port_out_info     = port_out_temp    ;
		ptr_setup_trace_info->wave_num_info     = wave_num_temp    ;
		
		op_prg_list_insert(lptr_exter_traffic_trace_info, ptr_setup_trace_info, OPC_LISTPOS_TAIL);
		
		/*�������˿�*/
/*		PORT_WAVE_LOCK[port_out_temp][wave_num_temp]=1;
		
				
		op_pk_send_delayed(pkptr, port_exter_rack[port_out_temp].outstrm_setup_index, packet_setup_length/(transmission_bandwidth*10000000));
		
		/* debug */
		/*
		printf("**********************ATTENTION***********************\n");
	    printf("op_sim_time (us) : %f\n",op_sim_time()*1000000);
	    printf("setup packet is sent from node (%d,%d%d%d%d) \n",local_cluster_id,local_position_id[3],local_position_id[2],local_position_id[1],local_position_id[0]);
		printf("PORT_WAVE_LOCK[%d][%d]: %d  \n",port_out_temp,wave_num_temp,PORT_WAVE_LOCK[port_out_temp][wave_num_temp]);
	   	*/
	
		
/*		}/*�������鴦����� */
	
/*	FOUT;
	

	
	
	
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*����lptr_exter_setup_candidate_info �Լ� lptr_exter_ack_candidate_info �����ٲã��趨��������ȼ�˳������Ϊ�������飬ack ���飬setup ���� */
/*
void exter_control_switch()
{

int portout_occupy_flag[6] ={-1,-1,-1,-1,-1,-1};

int ack_list_len     =-1;
int setup_list_len   =-1;
int tear_list_len    =-1;

int i = -1;



FIN(exter_control_switch());

/*���ȴ���teardown ���飬��lptr_exter_teardown_candidate_info ��Ϊ�գ����Ȼ�ܹ�ѡ������һ������鷢�ͣ��������ٴ���ö˿ڵ��������� */
/*for(i=0;i<6;i++)
	{
	tear_list_len = op_prg_list_size(lptr_exter_teardown_candidate_info[i]);
	
	if(tear_list_len ==0)
		{
		portout_occupy_flag[i]=0;
		continue;
		}
	else
		{
		portout_occupy_flag[i]=1;
		
		exter_tear_chose_to_send(tear_list_len,i);
		
		}
	
	
	}/* �Բ�������Ĵ������ */


/*����ack ���飬��lptr_exter_ack_candidate_info ��Ϊ�գ����Ȼ�ܹ�ѡ��ack���鷢�� */

/*for(i=0;i<6;i++)
	{
	
	if(portout_occupy_flag[i]==1)
		{
		continue;
		}
	else
		{
	       ack_list_len = op_prg_list_size(lptr_exter_ack_candidate_info[i]);
	       
		   if(ack_list_len !=0)
		   {
		  	
	    	exter_ack_chose_to_send(ack_list_len,i);
			
			portout_occupy_flag[i]=1;
		
		   }
	   }
	}/*��ACK����Ĵ������ */

/*��δ��� �������� */
/*���ڽ�������������´����� ��*/
/*1 ��Ƕ�Ӧ����˿ڵĶ�Ӧ����ռ�� 2 ��¼���������trace */
/*for(i=0;i<6;i++)
	{
	  if(portout_occupy_flag[i]==1)
	    {
		continue;		
		}
	  else
		  {
		  setup_list_len = op_prg_list_size(lptr_exter_setup_candidate_info[i]);
		  if(setup_list_len!=0)
	      {
		  exter_setup_chose_to_send(setup_list_len,i);
		  }
		  
		  
		  }
	
	  }

FOUT;


	
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void exter_candidate_list_empty()
	{
	int i;
	
	FIN(exter_candidate_list_empty());
	
	for(i=0;i<6;i++)
		{
		op_prg_list_free(lptr_exter_teardown_candidate_info[i]);
		
		}
	
	for(i=0;i<6;i++)
		{
		op_prg_list_free(lptr_exter_ack_candidate_info[i]);
		}
	
	for(i=0;i<6;i++)
		{
		op_prg_list_free(lptr_exter_setup_candidate_info[i]);
		
		}
	
	FOUT;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* ����6���˿ڵĴ�ת�� �������� */
/*
static void pk_teardown_arr_actions(Packet* pkptr,int instrm)
{
int dest_position_id_temp[4]={-1,-1,-1,-1};
int dest_cluster_id_temp = -1;
int i;

FIN(pk_teardown_arr_actions());

op_pk_fd_get(pkptr,DEST_POSITION_ID_0, &dest_position_id_temp[0]);
op_pk_fd_get(pkptr,DEST_POSITION_ID_1, &dest_position_id_temp[1]);
op_pk_fd_get(pkptr,DEST_POSITION_ID_2, &dest_position_id_temp[2]);
op_pk_fd_get(pkptr,DEST_POSITION_ID_3, &dest_position_id_temp[3]);

op_pk_fd_get(pkptr,DEST_CLUSTER_ID   , &dest_cluster_id_temp);

/* ����Ŀ�Ľڵ�Ĳ������飬���ٲ�������  */
/*
if(dest_position_id_temp[0]==local_position_id[0] && dest_position_id_temp[1]==local_position_id[1] && dest_position_id_temp[2]==local_position_id[2] && dest_position_id_temp[3]==local_position_id[3]
	&& dest_cluster_id_temp == local_cluster_id)
	{
	  /* debug */
	/*
	 printf("*****************************ATTENTION*********************\n");
	 printf(" TEAR DOWN PACKET ARRIVES AT NODE  :(%d,%d%d%d%d)\n",local_cluster_id,local_position_id[3],local_position_id[2],local_position_id[1],local_position_id[0]);
	 printf(" op_sim_time(us) : %f\n",op_sim_time()*1000000);
	*/
	/*
		op_pk_destroy(pkptr);
	}

/*���򣬽���������洢����Ӧ�Ķ����еȴ����� */
/* else
	{
	
	for(i=0;i<6;i++)
		{
		if(port_exter_rack[i].instrm_setup_index == instrm)
			{
			op_subq_pk_insert(TEARDOWN_SUBQ_BEGIN+1+i,pkptr,OPC_QPOS_TAIL);
			
			/* dubug */
			/*
			 printf("*****************************ATTENTION*********************\n");
			 printf(" TEAR DOWN PACKET ARRIVES AT NODE  :(%d,%d%d%d%d)\n",local_cluster_id,local_position_id[3],local_position_id[2],local_position_id[1],local_position_id[0]);
			 printf(" op_sim_time(us) : %f\n",op_sim_time()*1000000);
			 printf(" teardown packet is inserted subq: %d \n",TEARDOWN_SUBQ_BEGIN+1+i);
			*/
		/*	 break;
			}
		}
	
	}

FOUT;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* �����м�ת����setup �����Լ�����Ŀ�Ľڵ㣨rack���� SETUP ���� */
/*
		void pk_setup_arr_actions(Packet* pkptr, int instrm)
{
int opc_flow_num=0;

int dest_position_id[4] ={ 0,0,0,0 } ;
int dest_cluster_id = 0;

int sour_position_id[4]={-1,-1,-1,-1};
int sour_cluster_id =-1;

Packet * pkptr_ack ;

int wave_num;

int i=0;


FIN(pk_setup_arr_actions());
	
op_pk_fd_get(pkptr, ID_NO_OPC_FLOW ,     & opc_flow_num);
op_pk_fd_get(pkptr, DEST_POSITION_ID_0,  & dest_position_id[0]);
op_pk_fd_get(pkptr, DEST_POSITION_ID_1,  & dest_position_id[1]);
op_pk_fd_get(pkptr, DEST_POSITION_ID_2,  & dest_position_id[2]);
op_pk_fd_get(pkptr, DEST_POSITION_ID_3,  & dest_position_id[3]);

op_pk_fd_get(pkptr, WAVE_NUM          ,  & wave_num           );


op_pk_fd_get(pkptr, DEST_CLUSTER_ID,    & dest_cluster_id);



/*����Ŀ�Ľڵ�� setup ���� ������ ACK ���鲢������ */
/*
		if(dest_position_id[0]==local_position_id[0] && dest_position_id[1]==local_position_id[1] && dest_position_id[2] ==local_position_id[2] && dest_position_id[3]==local_position_id[3] && dest_cluster_id ==local_cluster_id)
	{
	
	op_pk_fd_get(pkptr,SOUR_POSITION_ID_0, &sour_position_id[0]);
	op_pk_fd_get(pkptr,SOUR_POSITION_ID_1, &sour_position_id[1]);
	op_pk_fd_get(pkptr,SOUR_POSITION_ID_2, &sour_position_id[2]);
	op_pk_fd_get(pkptr,SOUR_POSITION_ID_3, &sour_position_id[3]);
	
	op_pk_fd_get(pkptr,SOUR_CLUSTER_ID,    &sour_cluster_id);
	
	/* debug */
	/*
		printf("**********************ATTENTION***********************\n");
	    printf("op_sim_time(us)  : %f\n",op_sim_time()*1000000);
	    printf("setup packet arrive at destination: (%d,%d%d%d%d) \n",local_cluster_id,local_position_id[3],local_position_id[2],local_position_id[1],local_position_id[0]);
	*/
	
	/*����ACK ���� */
/*	pkptr_ack =op_pk_create(packet_ack_length);
	
	op_pk_encap_flag_set(pkptr_ack, OPC_ACK_FLAG);
	
	op_pk_fd_set(pkptr_ack, ID_NO_OPC_FLOW,OPC_FIELD_TYPE_INTEGER, opc_flow_num, 15);
	op_pk_fd_set(pkptr_ack, WAVE_NUM    ,OPC_FIELD_TYPE_INTEGER,  wave_num    ,   3);
	
	/*д��Դ��ַ��Ŀ�ĵ�ַ */
/*	op_pk_fd_set(pkptr_ack, SOUR_POSITION_ID_0,OPC_FIELD_TYPE_INTEGER,sour_position_id[0],2);
	op_pk_fd_set(pkptr_ack, SOUR_POSITION_ID_1,OPC_FIELD_TYPE_INTEGER,sour_position_id[1],2);
	op_pk_fd_set(pkptr_ack, SOUR_POSITION_ID_2,OPC_FIELD_TYPE_INTEGER,sour_position_id[2],2);
	op_pk_fd_set(pkptr_ack, SOUR_POSITION_ID_3,OPC_FIELD_TYPE_INTEGER,sour_position_id[3],2);
	op_pk_fd_set(pkptr_ack, SOUR_CLUSTER_ID   ,OPC_FIELD_TYPE_INTEGER,sour_cluster_id    ,3);
	
	op_pk_fd_set(pkptr_ack, DEST_POSITION_ID_0,OPC_FIELD_TYPE_INTEGER,dest_position_id[0],2);
	op_pk_fd_set(pkptr_ack, DEST_POSITION_ID_1,OPC_FIELD_TYPE_INTEGER,dest_position_id[1],2);
	op_pk_fd_set(pkptr_ack, DEST_POSITION_ID_2,OPC_FIELD_TYPE_INTEGER,dest_position_id[2],2);
	op_pk_fd_set(pkptr_ack, DEST_POSITION_ID_3,OPC_FIELD_TYPE_INTEGER,dest_position_id[3],2);
	
	op_pk_fd_set(pkptr_ack, DEST_CLUSTER_ID   ,OPC_FIELD_TYPE_INTEGER,dest_cluster_id    ,3);
	
	op_pk_total_size_set(pkptr_ack,packet_ack_length);
	/*dubug*/
	/*
	printf("****************************ATTENTION****************************\n");
	printf(" ACK  PACKET IS GENERATED at node (%d,%d%d%d%d)\n",local_cluster_id,local_position_id[3],local_position_id[2],local_position_id[1],local_position_id[0]);
	printf(" op_sim_time(us)  : %f\n",op_sim_time()*1000000);
	*/
	
	/*���� SETUP ���� */
	/*op_pk_destroy(pkptr);
	
	/*���� ���� ack ���� */
/*	
	for(i=0;i<6;i++)
		{
		if(port_exter_rack[i].instrm_setup_index == instrm)
			{
			op_pk_send_delayed(pkptr_ack,port_exter_rack[i].outstrm_setup_index,packet_setup_length/(transmission_bandwidth*10000000));
			break;
			}
		}
	
	
	}

/*�м�ڵ�� �������� ������������ڶ�Ӧ����˿ڵĶ����У�����Ҫ���ղ�ͬ�����ֱ�洢�ڲ�ͬ�Ķ����� */
/*
else
	{
		
	for(i=0;i<6;i++)
		{
		if(port_exter_rack[i].instrm_setup_index == instrm)
			{
			op_subq_pk_insert(SETUP_EXTER_SUBQ_BEGIN+i*15+wave_num , pkptr, OPC_QPOS_TAIL);
			/* debug */
			/*
			printf("**********************ATTENTION***********************\n");
	        printf("op_sim_time(us)  : %f\n",op_sim_time()*1000000);
	        printf("setup packet arrives at node (%d,%d%d%d%d) \n",local_cluster_id,local_position_id[3],local_position_id[2],local_position_id[1],local_position_id[0]);	
			printf("setup packet is inserted subq: %d\n",SETUP_EXTER_SUBQ_BEGIN+i*15+wave_num);
			*/
	/*		break;
			}
		}
	
	}

FOUT;

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  ���� 6 ���˿ڴ�ת���� ACK����  */
/*
static void pk_ack_arr_actions(Packet* pkptr, int instrm)
	
{
int sour_pos_id_temp[4]={-1,-1,-1,-1};
int sour_cluster_id_temp = -1;

int dest_position_id_temp[4]={-1,-1,-1,-1};
int dest_cluster_id_temp    =-1;

int i;
int opc_flow_num_temp   =-1;

LOCAL_SETUP_INFO* ptr_local_data_info;
LOCAL_OPC_INFO* ptr_local_traffic_send_info;

int list_len_temp = -1;

//int list_len_send =-1;

FIN(pk_ack_arr_actions());

op_pk_fd_get(pkptr,SOUR_POSITION_ID_0, &sour_pos_id_temp[0]);
op_pk_fd_get(pkptr,SOUR_POSITION_ID_1, &sour_pos_id_temp[1]);
op_pk_fd_get(pkptr,SOUR_POSITION_ID_2, &sour_pos_id_temp[2]);
op_pk_fd_get(pkptr,SOUR_POSITION_ID_3, &sour_pos_id_temp[3]);

op_pk_fd_get(pkptr,SOUR_CLUSTER_ID    , &sour_cluster_id_temp);


/*����ԴRACK�� ACK���飬�������Ų�ѯ���ݷ���Ķ��У����͸ö����е����ݷ��� */
/*
		if(sour_pos_id_temp[0]==local_position_id[0] && sour_pos_id_temp[1]==local_position_id[1] && sour_pos_id_temp[2]==local_position_id[2] && sour_pos_id_temp[3]==local_position_id[3]
	&& sour_cluster_id_temp == local_cluster_id)
	{
	op_pk_fd_get(pkptr,ID_NO_OPC_FLOW , &opc_flow_num_temp);
	op_pk_fd_get(pkptr,DEST_POSITION_ID_0, &dest_position_id_temp[0]);
	op_pk_fd_get(pkptr,DEST_POSITION_ID_1, &dest_position_id_temp[1]);
	op_pk_fd_get(pkptr,DEST_POSITION_ID_2, &dest_position_id_temp[2]);
	op_pk_fd_get(pkptr,DEST_POSITION_ID_3, &dest_position_id_temp[3]);
	op_pk_fd_get(pkptr,DEST_CLUSTER_ID   , &dest_cluster_id_temp);
	
	
	
	/*�������Ų�ѯ lptr_local_setup_info ,����ص���Ϣд�� lptr_lcoal_traffic_send_info �� */
	/*
		list_len_temp = op_prg_list_size(lptr_local_setup_info) ;
	
	for(i=0;i<list_len_temp;i++)
		{
		ptr_local_data_info = (LOCAL_SETUP_INFO*)op_prg_list_access(lptr_local_setup_info,i);
		
		if(ptr_local_data_info-> opc_flow_num_rec == opc_flow_num_temp)
			{
			
			ptr_local_traffic_send_info = (LOCAL_OPC_INFO*)op_prg_mem_alloc(sizeof(LOCAL_OPC_INFO));
			
			ptr_local_traffic_send_info -> opc_flow_num_s = ptr_local_data_info->opc_flow_num_rec ;
			ptr_local_traffic_send_info -> opc_subq_s =ptr_local_data_info->opc_data_subq_rec ;
			ptr_local_traffic_send_info -> port_out_s      =ptr_local_data_info->port_out_rec ;
			ptr_local_traffic_send_info -> wave_num_s      =ptr_local_data_info->wave_num_rec ;
			
			ptr_local_traffic_send_info -> dest_position_s[0]= dest_position_id_temp[0];
			ptr_local_traffic_send_info -> dest_position_s[1]= dest_position_id_temp[1];
			ptr_local_traffic_send_info -> dest_position_s[2]= dest_position_id_temp[2];
			ptr_local_traffic_send_info -> dest_position_s[3]= dest_position_id_temp[3];
			
			ptr_local_traffic_send_info -> dest_cluster_s    = dest_cluster_id_temp    ;
			
			op_prg_list_insert(lptr_local_traffic_send_info,ptr_local_traffic_send_info,OPC_LISTPOS_TAIL);
			
			}
		
			
		}
	
	
	/*����ACK ���� */
	
/*	
	op_pk_destroy(pkptr);
	
	op_intrpt_schedule_self(op_sim_time(),Local_Agg_Traffic_Send_Rolling);
	
	
	}
/*�м�ڵ��ACK ���飬��ACK����洢����Ӧ������˿�λ�� */
/* 
else
	{
	for(i=0;i<6;i++)
		{
		if(port_exter_rack[i].instrm_setup_index == instrm)
			{
			op_subq_pk_insert(ACK_SUBQ_BEGIN+i,pkptr,OPC_QPOS_TAIL);
			/*dubug*/
			/*
	printf("****************************ATTENTION****************************\n");
	printf(" op_sim_time(us)  : %f\n",op_sim_time()*1000000);
	printf(" ACK  PACKET arrives at node (%d,%d%d%d%d)\n",local_cluster_id,local_position_id[3],local_position_id[2],local_position_id[1],local_position_id[0]);
    printf(" ACK Packet has been inserted subq : %d \n",ACK_SUBQ_BEGIN+i);
			*/
	  /*      
			break;
			
			}
		  
			
		}
	}

FOUT;


}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void local_pk_optical_send(list_len_send)
{
   int i;
    
   LOCAL_OPC_INFO* ptr_local_opc_send ;
   
   int opc_flow_num_temp = 0;
   int opc_subq_num_temp  = 0;
   int port_out_temp     = 0;
   int wave_num_temp     = 0;
   Packet* pkptr_tear;
   Packet* pkptr_opc ;
   
   
   int* item_del_flow_num = OPC_NIL;
   
   int dest_position_id_t[4]={-1,-1,-1,-1};
   int dest_cluster_id_t    =-1;
   
   int t;
   int* del_flow_num_rec;
   LOCAL_OPC_INFO* ptr_opc_item;
   int list_len_opc;
   int k;
   
   int list_len_del ;
   
   Ici* iciptr = OPC_NIL ;
   
   int ID_num_temp=-1;
 
  
   
   
   FIN(local_pk_optical_send());
   

   
   
   for(i=0;i<list_len_send;i++)
   {
   ptr_local_opc_send =(LOCAL_OPC_INFO*)op_prg_list_access(lptr_local_traffic_send_info,i);
   
   opc_flow_num_temp = ptr_local_opc_send -> opc_flow_num_s ;
   opc_subq_num_temp = ptr_local_opc_send -> opc_subq_s     ;
   port_out_temp     = ptr_local_opc_send -> port_out_s     ;
   wave_num_temp     = ptr_local_opc_send -> wave_num_s     ;
   dest_position_id_t[0] = ptr_local_opc_send-> dest_position_s[0];
   dest_position_id_t[1] = ptr_local_opc_send-> dest_position_s[1];
   dest_position_id_t[2] = ptr_local_opc_send-> dest_position_s[2];
   dest_position_id_t[3] = ptr_local_opc_send-> dest_position_s[3];
   
   dest_cluster_id_t      = ptr_local_opc_send-> dest_cluster_s; 
   
   if(OPC_ST_PORT_LOCK[port_out_temp][wave_num_temp]==1)
	   {
	   continue;
	   }
   else
	   { 
   
           /*�������еķ����Ѿ�������� ��������������飬����������������� TEARDOWN_SUBQ_BEGIN */
       /*
		if(op_subq_empty(opc_subq_num_temp)==OPC_TRUE)
	       {
	         pkptr_tear =op_pk_create(packet_teardown_length);
	   
	         op_pk_encap_flag_set(pkptr_tear, OPC_TEARDOWN_FLAG);
	
	         op_pk_fd_set(pkptr_tear, ID_NO_OPC_FLOW,OPC_FIELD_TYPE_INTEGER, opc_flow_num_temp, 15);
	         op_pk_fd_set(pkptr_tear, WAVE_NUM      ,OPC_FIELD_TYPE_INTEGER,  wave_num_temp   ,   3);
	
	         /*д��Դ��ַ��Ŀ�ĵ�ַ */
	     /*    op_pk_fd_set(pkptr_tear, SOUR_POSITION_ID_0,OPC_FIELD_TYPE_INTEGER,local_position_id[0],2);
	         op_pk_fd_set(pkptr_tear, SOUR_POSITION_ID_1,OPC_FIELD_TYPE_INTEGER,local_position_id[1],2);
	         op_pk_fd_set(pkptr_tear, SOUR_POSITION_ID_2,OPC_FIELD_TYPE_INTEGER,local_position_id[2],2);
	         op_pk_fd_set(pkptr_tear, SOUR_POSITION_ID_3,OPC_FIELD_TYPE_INTEGER,local_position_id[3],2);
	         op_pk_fd_set(pkptr_tear, SOUR_CLUSTER_ID   ,OPC_FIELD_TYPE_INTEGER,local_cluster_id    ,3);
	
	         op_pk_fd_set(pkptr_tear, DEST_POSITION_ID_0,OPC_FIELD_TYPE_INTEGER,dest_position_id_t[0],2);
	         op_pk_fd_set(pkptr_tear, DEST_POSITION_ID_1,OPC_FIELD_TYPE_INTEGER,dest_position_id_t[1],2);
	         op_pk_fd_set(pkptr_tear, DEST_POSITION_ID_2,OPC_FIELD_TYPE_INTEGER,dest_position_id_t[2],2);
	         op_pk_fd_set(pkptr_tear, DEST_POSITION_ID_3,OPC_FIELD_TYPE_INTEGER,dest_position_id_t[3],2);
	
	         op_pk_fd_set(pkptr_tear, DEST_CLUSTER_ID   ,OPC_FIELD_TYPE_INTEGER,dest_cluster_id_t    ,3);
	
	         op_pk_total_size_set(pkptr_tear,packet_teardown_length);
	   
	         op_subq_pk_insert(TEARDOWN_SUBQ_BEGIN, pkptr_tear, OPC_QPOS_TAIL);
			 
			 /*debug*/
			 /*
			 printf("*****************************ATTENTION*********************\n");
			 printf(" TEAR DOWN PACKET GENERATES AT NODE  :(%d,%d%d%d%d)\n",local_cluster_id,local_position_id[3],local_position_id[2],local_position_id[1],local_position_id[0]);
			 printf(" The flow id of the teardown packet: %d\n",opc_flow_num_temp);
			 printf(" op_sim_time(us) : %f\n",op_sim_time()*1000000);
			 printf("************************************************************\n\n");
			 */
	   
	          /* ��¼����Ŀ��λ�ã�׼��ɾ������Ŀ */
			 
	   /*
	         item_del_flow_num = (int*)op_prg_mem_alloc(sizeof(int));
			 *item_del_flow_num = opc_flow_num_temp ;
	         op_prg_list_insert(lptr_item_del_info,item_del_flow_num ,OPC_LISTPOS_TAIL);
	    
			 }
		
   
       
       /*�����в�Ϊ�գ��Ӷ��е�ͷ����ȡ���飬�޸ķ�������ţ����͸÷��飻2����ס����˿� OPC_ST_PORT_LOCK,����ICI��Ϣ������һ����ѯ����֮ǰ��������˿� */
       
		/*else
	        {
	          
	   
	   
	         pkptr_opc = op_subq_pk_remove(opc_subq_num_temp,OPC_QPOS_HEAD);
			 
			 
			 /* debug */
			/* op_pk_fd_get(pkptr_opc,ID_NO, &ID_num_temp);
			 
			 /*
			 printf("****************ATTENTION******************\n");
			 printf(" op_sim_time(us)              : %f    \n",op_sim_time()*1000000);
			 printf(" opc_packet is send from node :(%d,%d%d%d%d)\n", local_cluster_id,local_position_id[3],local_position_id[2],local_position_id[1],local_position_id[0]);
			 printf(" ID NUMBER OF THE OPC PACKET  : %d \n", ID_num_temp);
			 printf(" subq of the opc packet       : %d\n ", opc_subq_num_temp);
			 */
			
			 
			 
			 /*
	   
	         op_pk_encap_flag_set(pkptr_opc, OPC_EXTER_FLAG);
	   
	         op_pk_fd_set(pkptr_opc, ID_NO_OPC_FLOW, OPC_FIELD_TYPE_INTEGER, opc_flow_num_temp ,15);
	   
	         op_pk_send_delayed(pkptr_opc, port_exter_rack[port_out_temp].outstrm_wave_channel[wave_num_temp],packet_data_length/(transmission_bandwidth*10000000));
			 
			 OPC_ST_PORT_LOCK[port_out_temp][wave_num_temp]=1;
			 
			 /* debug */
			// printf(" OPC_ST_PORT_LOCK[%d][%d]=%d\n\n",port_out_temp,wave_num_temp,OPC_ST_PORT_LOCK[port_out_temp][wave_num_temp]);
			 
			 /*�� ICI */
		/*
			 iciptr = op_ici_create("OPC_ST_STATE_FREE");
			 op_ici_attr_set(iciptr,"port_out_free",port_out_temp);
			 op_ici_attr_set(iciptr,"wave_num_free",wave_num_temp);
			 op_ici_install(iciptr);
			 
			 op_intrpt_schedule_self(op_sim_time()+(packet_data_length-0.5)/(transmission_bandwidth*10000000), OPC_Port_Out_State_Free);
			 
			 }
			
		}/*end if OPC_ST_PORT_LOCK[port_out_temp][wave_num_temp]!=1*/
 /* }
   
   
   /* debug */
   /*
   list_len_lts = op_prg_list_size(lptr_item_del_info);
   for(k=0;k<list_len_lts;k++)
	   {
	   list_con_del = (int*)op_prg_list_access(lptr_item_del_info,k);
	   printf("del item : %d\n",*list_con_del);
	   }
   
   list_len_lts = op_prg_list_size(lptr_local_traffic_send_info);
   printf(" DEL Before \n");
   for(k=0;k<list_len_lts;k++)
	   {
	   
	   list_con_opc =(LOCAL_OPC_INFO*)op_prg_list_access(lptr_local_traffic_send_info,k);
	   printf(" flow num of the list :%d\n",list_con_opc->opc_flow_num_s);
	   
	   }
   */
   		
   
         /*���� lptr_item_del_info �м�¼������ɾ�� lptr_local_traffic_send_info �е����� */
   /*       
   list_len_del = op_prg_list_size(lptr_item_del_info);
   
           if(list_len_del != 0)
        	{
	           for(t=0;t<list_len_del;t++)
		       {
	     
		        del_flow_num_rec = (int*)op_prg_list_access(lptr_item_del_info,t);
				list_len_opc = op_prg_list_size(lptr_local_traffic_send_info);
				
				for(k=0;k<list_len_opc;k++)
					{
					
					ptr_opc_item = (LOCAL_OPC_INFO*)op_prg_list_access(lptr_local_traffic_send_info,k);
					if(ptr_opc_item ->opc_flow_num_s == *del_flow_num_rec)
						{
						op_prg_list_remove(lptr_local_traffic_send_info, k);
						break;
						}
					}
		
		        		
		        }
	         }
   
   
           /*��� lptr_item_del_info �е���Ϣ */
   /*
            op_prg_list_free(lptr_item_del_info);
			
  
   FOUT;
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void pk_exter_opc_arr_actions(Packet* pkptr, int instrm)
{
int dest_position_id_t[4]={-1,-1,-1,-1};
int dest_cluster_id_t =-1;


int dest_server_id_t  =-1;

int port_out_t;
int wave_num_t;
int opc_flow_num_t ;


TRACE_INFO* opc_trace_info =OPC_NIL ;
int i=0;

int list_len_trace;

FIN(pk_exter_opc_arr_actions());

op_pk_fd_get(pkptr,DEST_POSITION_ID_0,&dest_position_id_t[0]);
op_pk_fd_get(pkptr,DEST_POSITION_ID_1,&dest_position_id_t[1]);
op_pk_fd_get(pkptr,DEST_POSITION_ID_2,&dest_position_id_t[2]);
op_pk_fd_get(pkptr,DEST_POSITION_ID_3,&dest_position_id_t[3]);

op_pk_fd_get(pkptr,DEST_CLUSTER_ID   ,&dest_cluster_id_t   );

/* ��������Ѿ�����Ŀ�Ľڵ㣬��洢��������۽��ն����� */
   
   /*
 if(dest_position_id_t[0] == local_position_id[0] && dest_position_id_t[1] == local_position_id[1] && dest_position_id_t[2] ==local_position_id[2] && dest_position_id_t[3] == local_position_id[3]
	 && dest_cluster_id_t == local_cluster_id)
	 {
	 op_pk_fd_get(pkptr,DEST_SERVER_ID, &dest_server_id_t);
	 
	 op_subq_pk_insert(AGG_QUEUE_RVD_BEGIN+dest_server_id_t , pkptr ,OPC_QPOS_TAIL);
	 
	 /* debug */
	 /*
	 printf(" opc packet has arrive at node:(%d,%d%d%d%d)\n",local_cluster_id,local_position_id[3],local_position_id[2],local_position_id[1],local_position_id[0]);
	 printf(" op_sim_time(us)   :     %f\n", op_sim_time()*1000000);
	 printf(" opc packet is inserted subq : %d         \n", AGG_QUEUE_RVD_BEGIN+dest_server_id_t);
	 */
	 
//	 }

/*�������������Ľڵ�Ϊ�м�ڵ� ������ݷ�������Ų�ѯ lptr_exter_traffic_trace_info ��Ȼ�������Ӧ������˿ںͲ������ת���ù���� */
/*
	 else
	{
	op_pk_fd_get(pkptr, ID_NO_OPC_FLOW, &opc_flow_num_t);
	
	/* debug */
	/*
	printf(" opc packet has arrive at the node:(%d,%d%d%d%d)\n",local_cluster_id,local_position_id[3],local_position_id[2],local_position_id[1],local_position_id[0]);
	printf(" op_sim_time (us)   :%f\n    ",op_sim_time()*1000000);
	*/
/*	
	
	list_len_trace = op_prg_list_size(lptr_exter_traffic_trace_info);
	
	for(i=0;i<list_len_trace;i++)
		{
	      opc_trace_info = (TRACE_INFO*) op_prg_list_access(lptr_exter_traffic_trace_info,i);
		  
		  if(opc_trace_info->flow_opc_num_info == opc_flow_num_t)
			  {
			  port_out_t = opc_trace_info-> port_out_info;			  
			  wave_num_t = opc_trace_info-> wave_num_info;
			  break;			  
			  }	
		  	
		}
	
	op_pk_send_forced(pkptr,port_exter_rack[port_out_t].outstrm_wave_channel[wave_num_t]);
	
	}

FOUT;



}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void opc_st_free(Ici* ici_opc_st_free)
{
int port_out_temp;
int wave_num_temp;


FIN(opc_st_free());

op_ici_attr_get(ici_opc_st_free, "port_out_free", &port_out_temp);
op_ici_attr_get(ici_opc_st_free, "wave_num_free", &wave_num_temp);

OPC_ST_PORT_LOCK[port_out_temp][wave_num_temp]=0;

/*debug*/
/*
printf("op_sim_time(us)   :%f   \n",op_sim_time()*1000000);
printf("OPC_ST_PORT_LOCK[%d][%d] =  %d \n", port_out_temp, wave_num_temp,OPC_ST_PORT_LOCK[port_out_temp][wave_num_temp]);
*/
/*
op_ici_destroy(ici_opc_st_free);

FOUT;




}
*/



  

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
	void Oarst_AWGR_Switch (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Obtype _op_Oarst_AWGR_Switch_init (int * init_block_ptr);
	void _op_Oarst_AWGR_Switch_diag (OP_SIM_CONTEXT_ARG_OPT);
	void _op_Oarst_AWGR_Switch_terminate (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Address _op_Oarst_AWGR_Switch_alloc (VosT_Obtype, int);
	void _op_Oarst_AWGR_Switch_svar (void *, const char *, void **);


#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
Oarst_AWGR_Switch (OP_SIM_CONTEXT_ARG_OPT)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	FIN_MT (Oarst_AWGR_Switch ());

		{
		/* Temporary Variables */
		Packet          *pkptr    = OPC_NIL;
		int              i        =0       ;
		/*
		Objid            server_objid = OPC_NIL;
		Objid            rx_strm_objid  ;
		
		Objid            tx_strm_objid  ;
		int              rx_strm_index;
		int              tx_strm_index;
		int              server_num_temp;
		*/
		int              instrm = 0;
		
		
		
		Objid            rx_strm_objid_elec = OPC_NIL;
		/*
		Objid            rx_strm_objid_opc_0 ;
		Objid            rx_strm_objid_opc_1 ;
		Objid            rx_strm_objid_opc_2 ;
		Objid            rx_strm_objid_opc_3 ;
		*/
		
		int              rx_strm_index_elec =OPC_NIL;
		/*
		int              rx_strm_index_opc_0;
		int              rx_strm_index_opc_1 ;
		int              rx_strm_index_opc_2 ;
		int              rx_strm_index_opc_3 ;
		*/
		
		Objid            tx_strm_objid_elec=OPC_NIL ;
		/*
		Objid            tx_strm_objid_opc_0;
		Objid            tx_strm_objid_opc_1 ;
		Objid            tx_strm_objid_opc_2 ;
		Objid            tx_strm_objid_opc_3 ;
		*/
		
		
		int              tx_strm_index_elec =OPC_NIL ;
		/*
		int              tx_strm_index_opc_0 ; 
		int              tx_strm_index_opc_1  ;
		int              tx_strm_index_opc_2  ; 
		int              tx_strm_index_opc_3  ; 
		*/
		
		
		Objid            rx_objid =OPC_NIL;
		
		
		Objid            link_objid =OPC_NIL ;
		Objid            remote_tx_objid = OPC_NIL ;
		Objid            remote_node_objid= OPC_NIL;
		
		//int              remote_net_index = -1;
		int              remote_group_index = -1;
		int              remote_switch_index=-1;
		//int              remote_unique_index=-1;
		int              remote_server_index=-1;
		
		int              port_temp=-1;
		
		
		 Objid           tx_objid;
		
		int              j=0;
		
		
		int              list_len_send = 0 ;
		/////////////////////////////////////////////////////////
		//Ici*             ici_opc_st_free ;
		
		/* End of Temporary Variables */


		FSM_ENTER ("Oarst_AWGR_Switch")

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (initial) enter executives **/
			FSM_STATE_ENTER_FORCED_NOLABEL (0, "initial", "Oarst_AWGR_Switch [initial enter execs]")
				FSM_PROFILE_SECTION_IN ("Oarst_AWGR_Switch [initial enter execs]", state0_enter_exec)
				{
				/* �õ������̵�objid */
				
				own_objid = op_id_self ();
				
				/* Get the "switch" objid   */
				node_objid=op_topo_parent(own_objid);
				
				//op_ima_obj_attr_get (node_objid, "node_net_index", &local_net_id);
				
				/*���Position_ID ���� 4ά������ */
				op_ima_obj_attr_get (node_objid, "node_group_index", &local_group_id);
				op_ima_obj_attr_get (node_objid, "node_switch_index", &local_switch_id);
				//op_ima_obj_attr_get (node_objid, "node_unique_index", &local_unique_id);//���ܼ�һ��
				
				
				
				
				op_ima_sim_attr_get (OPC_IMA_DOUBLE, "Setup Packet Length(bits)",&packet_setup_length);
				op_ima_sim_attr_get (OPC_IMA_DOUBLE, "Data Packet Length(bits)", &packet_data_length);
				op_ima_sim_attr_get (OPC_IMA_DOUBLE, "ACK packet length(bits)", &packet_ack_length);
				op_ima_sim_attr_get (OPC_IMA_DOUBLE, "TEARDOWN packet length(bits)", &packet_teardown_length);
				
				op_ima_sim_attr_get (OPC_IMA_DOUBLE, "Electrical Transmission Bandwidth(bps)", &transmission_bandwidth_ele);
				op_ima_sim_attr_get (OPC_IMA_DOUBLE, "Optical Transmission Bandwidth(bps)", &transmission_bandwidth_opc);
				
				op_ima_sim_attr_get (OPC_IMA_INTEGER, "Port Number", &port_num);//�˿����ʵ��޸�
				
				
				
				/*����洢�˿���Ϣ�Ľṹ��*/
				eport_info = (EPORT_INFO*)op_prg_mem_alloc(4*sizeof(EPORT_INFO)) ;
				
				/*��ʼ�� k���˿� */
				
				for(i=0;i<4;i++)//i=8
					{
					eport_info[i].instrm_index_elec =-1;
					eport_info[i].outstrm_index_elec =-1;
					
					}
				
				
				
				/*��k������Ķ˿�*/
				
				for(i=0; i<4; i++)//i�޸�
					
					{
					
					/*��i�����Ż� id */
					rx_objid = op_topo_assoc(own_objid,OPC_TOPO_ASSOC_IN, OPC_OBJTYPE_PTRX,i);
					
					/*���� ��·�� id */
					if(op_topo_assoc(rx_objid,OPC_TOPO_ASSOC_IN,OPC_OBJTYPE_LKDUP,0) == OPC_OBJID_INVALID)
						continue;
					else		
						link_objid = op_topo_assoc(rx_objid,OPC_TOPO_ASSOC_IN,OPC_OBJTYPE_LKDUP,0);
					
					/*��Ѱ�Զ˵� TX_OBJID */
				
						 remote_tx_objid =op_topo_assoc(link_objid,OPC_TOPO_ASSOC_IN,OPC_OBJTYPE_PTTX,0);
						 if(op_topo_parent(remote_tx_objid) == node_objid)
						 remote_tx_objid = op_topo_assoc(link_objid,OPC_TOPO_ASSOC_IN,OPC_OBJTYPE_PTTX,1);
					
					/* �������Զ� �ڵ� */	
						 remote_node_objid = op_topo_parent(remote_tx_objid);
					
					/*��öԶ˽ڵ�ĵ�ַ��Ϣ */
					//  op_ima_obj_attr_get(remote_node_objid, "node_net_index", &remote_net_index);
					    op_ima_obj_attr_get(remote_node_objid, "node_group_index", &remote_group_index);
					    op_ima_obj_attr_get(remote_node_objid, "node_switch_index", &remote_switch_index);
				  //    op_ima_obj_attr_get(remote_node_objid, "node_unique_index", &remote_unique_index);
					
					/* ȷ���˿ڵĶ˿ں� */
					/*1 �жϱ��������Ǻ��Ĳ㽻�������߻�۲㽻���� */
					
					//   if(local_pod_id == port_num)/* ������Ϊ���Ĳ㽻�������˿ں�Ϊ�����ӻ�۲㽻������POD�� */
					//     {
					//	 port_temp = remote_pod_index;		
					//     }
					//  else /*������Ϊ��۲㽻���� ���������ж˿� */
					//	  {
					//	  if(remote_pod_index == port_num) /* ���������Ĳ㽻���������ж˿� */
					//		  {
					//		  port_temp = (remote_unique_index-1)+port_num/2;
					//		  }
					//	  else /*�����²㽻���� */
					//		  {
					//		  port_temp = remote_switch_index;
					//		  }
					//		  
					//	  
					//	  }
					
					
				
						port_temp = remote_group_index;
					
					 
					
					/* ������Ӧ�ķ��Ż� */
					tx_objid = 	op_topo_assoc(link_objid,OPC_TOPO_ASSOC_IN,OPC_OBJTYPE_PTTX,0);
					if(op_topo_parent(tx_objid) != node_objid)
					tx_objid = op_topo_assoc(link_objid,OPC_TOPO_ASSOC_IN,OPC_OBJTYPE_PTTX,1);   
					
					
					/* �󶨶˿ں��Լ������������� */
					
					/* ���Ҷ˵����ж˿�Ϊ��˿� ���ӵĽ�����Ϊ�⽻���� */
				
				
						rx_strm_objid_elec = op_topo_connect(rx_objid, own_objid, OPC_OBJTYPE_STRM , 0);
						op_ima_obj_attr_get(rx_strm_objid_elec,"dest stream", & rx_strm_index_elec);
						
						tx_strm_objid_elec = op_topo_connect(own_objid, tx_objid, OPC_OBJTYPE_STRM, 0);
						op_ima_obj_attr_get(tx_strm_objid_elec, "src stream", & tx_strm_index_elec);
						
						eport_info[port_temp].instrm_index_elec  = rx_strm_index_elec ;
						eport_info[port_temp].outstrm_index_elec = tx_strm_index_elec ;		
						
					}
				
				
				
				
				
				/*��ʼ�� k���˿ڵ������ٲ��б� */
				/*3.21
				for(i=0;i<8;i++)
					{
					lptr_top_elec_candidate_info[i] = op_prg_list_create();
					}
				
				lptr_top_elec_routing_trace_info = op_prg_list_create();
				3.21*/
				/*ͳ����ע��*/
				stat_conf_count = 0;
				stat_conf_handle = op_stat_reg("stat_conf_local",OPC_STAT_INDEX_NONE,OPC_STAT_LOCAL);
				
				op_intrpt_schedule_self(op_sim_time(), Top_Elec_Switching);
				
				}
				FSM_PROFILE_SECTION_OUT (state0_enter_exec)

			/** state (initial) exit executives **/
			FSM_STATE_EXIT_FORCED (0, "initial", "Oarst_AWGR_Switch [initial exit execs]")


			/** state (initial) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "initial", "idle", "tr_5", "Oarst_AWGR_Switch [initial -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (idle) enter executives **/
			FSM_STATE_ENTER_UNFORCED (1, "idle", state1_enter_exec, "Oarst_AWGR_Switch [idle enter execs]")

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (3,"Oarst_AWGR_Switch")


			/** state (idle) exit executives **/
			FSM_STATE_EXIT_UNFORCED (1, "idle", "Oarst_AWGR_Switch [idle exit execs]")


			/** state (idle) transition processing **/
			FSM_PROFILE_SECTION_IN ("Oarst_AWGR_Switch [idle trans conditions]", state1_trans_conds)
			FSM_INIT_COND (PK_ARRIVAL)
			FSM_TEST_COND (TOP_ELEC_SWITCH)
			FSM_TEST_COND (END_SIM)
			FSM_DFLT_COND
			FSM_TEST_LOGIC ("idle")
			FSM_PROFILE_SECTION_OUT (state1_trans_conds)

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 2, state2_enter_exec, ;, "PK_ARRIVAL", "", "idle", "PK_ARRIVAL", "tr_8", "Oarst_AWGR_Switch [idle -> PK_ARRIVAL : PK_ARRIVAL / ]")
				FSM_CASE_TRANSIT (1, 3, state3_enter_exec, ;, "TOP_ELEC_SWITCH", "", "idle", "Top_Eelc_Sw", "tr_9", "Oarst_AWGR_Switch [idle -> Top_Eelc_Sw : TOP_ELEC_SWITCH / ]")
				FSM_CASE_TRANSIT (2, 4, state4_enter_exec, ;, "END_SIM", "", "idle", "stat_collect", "tr_10", "Oarst_AWGR_Switch [idle -> stat_collect : END_SIM / ]")
				FSM_CASE_TRANSIT (3, 1, state1_enter_exec, ;, "default", "", "idle", "idle", "tr_11", "Oarst_AWGR_Switch [idle -> idle : default / ]")
				}
				/*---------------------------------------------------------*/



			/** state (PK_ARRIVAL) enter executives **/
			FSM_STATE_ENTER_FORCED (2, "PK_ARRIVAL", state2_enter_exec, "Oarst_AWGR_Switch [PK_ARRIVAL enter execs]")
				FSM_PROFILE_SECTION_IN ("Oarst_AWGR_Switch [PK_ARRIVAL enter execs]", state2_enter_exec)
				{
				instrm = op_intrpt_strm();
				pkptr  = op_pk_get(instrm);
				
				flow_pk_arrival_actions(pkptr, instrm);
				
				//3.21
				top_elec_routing_computation();
				
				//////////////////////////////////////////////////////////////////////////////
				
				
				}
				FSM_PROFILE_SECTION_OUT (state2_enter_exec)

			/** state (PK_ARRIVAL) exit executives **/
			FSM_STATE_EXIT_FORCED (2, "PK_ARRIVAL", "Oarst_AWGR_Switch [PK_ARRIVAL exit execs]")


			/** state (PK_ARRIVAL) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "PK_ARRIVAL", "idle", "tr_6", "Oarst_AWGR_Switch [PK_ARRIVAL -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (Top_Eelc_Sw) enter executives **/
			FSM_STATE_ENTER_FORCED (3, "Top_Eelc_Sw", state3_enter_exec, "Oarst_AWGR_Switch [Top_Eelc_Sw enter execs]")
				FSM_PROFILE_SECTION_IN ("Oarst_AWGR_Switch [Top_Eelc_Sw enter execs]", state3_enter_exec)
				{
				//printf("rack_internal_switching\n");
				//3.21top_elec_routing_computation();
				//3.21top_elec_candidate_rolling();
				//3.21top_elec_candidate_list_empty();
				
				//////////////////////////////////////////////////////////////////////////////
				
				
				op_intrpt_schedule_self(op_sim_time()+ (packet_data_length/(10*transmission_bandwidth_opc)), Top_Elec_Switching);
				}
				FSM_PROFILE_SECTION_OUT (state3_enter_exec)

			/** state (Top_Eelc_Sw) exit executives **/
			FSM_STATE_EXIT_FORCED (3, "Top_Eelc_Sw", "Oarst_AWGR_Switch [Top_Eelc_Sw exit execs]")


			/** state (Top_Eelc_Sw) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "Top_Eelc_Sw", "idle", "tr_7", "Oarst_AWGR_Switch [Top_Eelc_Sw -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (stat_collect) enter executives **/
			FSM_STATE_ENTER_UNFORCED (4, "stat_collect", state4_enter_exec, "Oarst_AWGR_Switch [stat_collect enter execs]")
				FSM_PROFILE_SECTION_IN ("Oarst_AWGR_Switch [stat_collect enter execs]", state4_enter_exec)
				{
				op_stat_write(stat_conf_handle,stat_conf_count);
				}
				FSM_PROFILE_SECTION_OUT (state4_enter_exec)

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (9,"Oarst_AWGR_Switch")


			/** state (stat_collect) exit executives **/
			FSM_STATE_EXIT_UNFORCED (4, "stat_collect", "Oarst_AWGR_Switch [stat_collect exit execs]")


			/** state (stat_collect) transition processing **/
			FSM_TRANSIT_MISSING ("stat_collect")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (0,"Oarst_AWGR_Switch")
		}
	}




void
_op_Oarst_AWGR_Switch_diag (OP_SIM_CONTEXT_ARG_OPT)
	{
	/* No Diagnostic Block */
	}




void
_op_Oarst_AWGR_Switch_terminate (OP_SIM_CONTEXT_ARG_OPT)
	{

	FIN_MT (_op_Oarst_AWGR_Switch_terminate ())


	/* No Termination Block */

	Vos_Poolmem_Dealloc (op_sv_ptr);

	FOUT
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in _op_Oarst_AWGR_Switch_svar function. */
#undef eport_info
#undef own_objid
#undef node_objid
#undef packet_setup_length
#undef packet_data_length
#undef transmission_bandwidth_ele
#undef packet_ack_length
#undef packet_teardown_length
#undef local_group_id
#undef local_switch_id
#undef transmission_bandwidth_opc
#undef port_num
#undef lptr_top_elec_candidate_info
#undef lptr_elec_routing_trace_info
#undef lptr_top_elec_routing_trace_info
#undef stat_conf_handle
#undef stat_conf_count
#undef local_server_id

#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE

#define FIN_PREAMBLE_DEC
#define FIN_PREAMBLE_CODE

VosT_Obtype
_op_Oarst_AWGR_Switch_init (int * init_block_ptr)
	{
	VosT_Obtype obtype = OPC_NIL;
	FIN_MT (_op_Oarst_AWGR_Switch_init (init_block_ptr))

	obtype = Vos_Define_Object_Prstate ("proc state vars (Oarst_AWGR_Switch)",
		sizeof (Oarst_AWGR_Switch_state));
	*init_block_ptr = 0;

	FRET (obtype)
	}

VosT_Address
_op_Oarst_AWGR_Switch_alloc (VosT_Obtype obtype, int init_block)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	Oarst_AWGR_Switch_state * ptr;
	FIN_MT (_op_Oarst_AWGR_Switch_alloc (obtype))

	ptr = (Oarst_AWGR_Switch_state *)Vos_Alloc_Object (obtype);
	if (ptr != OPC_NIL)
		{
		ptr->_op_current_block = init_block;
#if defined (OPD_ALLOW_ODB)
		ptr->_op_current_state = "Oarst_AWGR_Switch [initial enter execs]";
#endif
		}
	FRET ((VosT_Address)ptr)
	}



void
_op_Oarst_AWGR_Switch_svar (void * gen_ptr, const char * var_name, void ** var_p_ptr)
	{
	Oarst_AWGR_Switch_state		*prs_ptr;

	FIN_MT (_op_Oarst_AWGR_Switch_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (void *)OPC_NIL;
		FOUT
		}
	prs_ptr = (Oarst_AWGR_Switch_state *)gen_ptr;

	if (strcmp ("eport_info" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->eport_info);
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
	if (strcmp ("transmission_bandwidth_ele" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->transmission_bandwidth_ele);
		FOUT
		}
	if (strcmp ("packet_ack_length" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->packet_ack_length);
		FOUT
		}
	if (strcmp ("packet_teardown_length" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->packet_teardown_length);
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
	if (strcmp ("transmission_bandwidth_opc" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->transmission_bandwidth_opc);
		FOUT
		}
	if (strcmp ("port_num" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->port_num);
		FOUT
		}
	if (strcmp ("lptr_top_elec_candidate_info" , var_name) == 0)
		{
		*var_p_ptr = (void *) (prs_ptr->lptr_top_elec_candidate_info);
		FOUT
		}
	if (strcmp ("lptr_elec_routing_trace_info" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->lptr_elec_routing_trace_info);
		FOUT
		}
	if (strcmp ("lptr_top_elec_routing_trace_info" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->lptr_top_elec_routing_trace_info);
		FOUT
		}
	if (strcmp ("stat_conf_handle" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->stat_conf_handle);
		FOUT
		}
	if (strcmp ("stat_conf_count" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->stat_conf_count);
		FOUT
		}
	if (strcmp ("local_server_id" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->local_server_id);
		FOUT
		}
	*var_p_ptr = (void *)OPC_NIL;

	FOUT
	}

