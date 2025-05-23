/* Process model C form file: Oars_Switch.pr.c */
/* Portions of this file copyright 1986-2008 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
const char Oars_Switch_pr_c [] = "MIL_3_Tfile_Hdr_ 145A 30A op_runsim 7 60A47757 60A47757 1 DESKTOP-L75PK39 ANTL 0 0 none none 0 0 none 0 0 0 0 0 0 0 0 1bcc 1                                                                                                                                                                                                                                                                                                                                                                                                   ";
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
/*定义各种队列的起始标志 */
///////////////////////////////////////////////////////////
/* 定义中断码 */
#define Edg_Elec_Switching              0

//#define  Agg_Traffic_Rolling            1
//#define  Edg_Elep_Send_Rolling          2




#define	 START			0
#define	 GENERATE			1




///////////////////////////////////////////////////////////////
/*定义状态转移的条件*/

# define     PK_ARRIVAL             (op_intrpt_type()==OPC_INTRPT_STRM)
# define     EDG_ELEC_SWITCH        (op_intrpt_type() == OPC_INTRPT_SELF) &&(op_intrpt_code()== Edg_Elec_Switching)
# define     END_SIM                (op_intrpt_type() == OPC_INTRPT_ENDSIM)
/*
# define     AGG_TRAFFIC_ROLLING    (op_intrpt_type() == OPC_INTRPT_SELF) &&(op_intrpt_code()== Agg_Traffic_Rolling )
# define     EDG_ELEP_SEND_ROLLING  (op_intrpt_type() == OPC_INTRPT_SELF) &&(op_intrpt_code()==Edg_Elep_Send_Rolling)*/






//#define OPC_PORT_OUT_STATE_FREE  (op_intrpt_type() == OPC_INTRPT_SELF) && (op_intrpt_code() == OPC_Port_Out_State_Free)




//////////////////////////////////////////////////////////////
/*定义分组域*/
/*定义分组域*/
#define ID_NO				  0	

#define  SOUR_GROUP_INDEX      1

#define  SOUR_SWITCH_INDEX     2

#define  SOUR_SERVER_INDEX     3
//可能加一项
#define  DEST_GROUP_INDEX      4

#define  DEST_SWITCH_INDEX     5

#define  DEST_SERVER_INDEX     6




////////////////////////////////
/* 定义不同分组的标记 */

#define PK_DATA_FLAG          0

#define OPC_SETUP_FLAG        1
#define OPC_ACK_FLAG          2
#define OPC_NACK_FLAG         3
#define OPC_ELEP_FLAG         4
#define OPC_TEARDOWN_FLAG     5

/////////////////////////////////////////////////////////////
/*定义全局变量 */
//long int elep_flow_num_global =0;

//////////////////////////////////////////////////////////
/*定义结构体存储rack内交换的端口 */
typedef struct
	{
	int outstrm_index_elec;
	int instrm_index_elec;
	
	}PORT_INFO;

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
/* 函数声明 */

static void elec_pk_arr_actions(Packet *pkptr,int instrm);
/*
static void ack_pk_arr_actions(Packet *pkptr,int instrm);
static void nack_pk_arr_actions(Packet *pkptr , int instrm);
static void elep_pk_arr_actions(Packet *pkptr,int instrm);
static void edg_teardown_pk_arr_actions(Packet* pkptr, int instrm);
static void edg_setup_pk_arr_actions(Packet *pkptr,int instrm);
*/


static void edg_elec_routing_computation();
static void edg_elec_candidate_chose_to_send(int list_len ,int i);
static void edg_elec_candidate_rolling();
static void edg_elec_candidate_list_empty();
/*
static void edg_agg_setup_gen();
static void edg_agg_setup_send();
static void edg_teardown_send();
*/







////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
void local_candidate_chose_to_send(int list_len, int i);
void local_candidate_rolling();
void local_candidate_list_empty();
static int wave_allocation(int dest_cluster_id, int dest_position_id_0,int dest_position_id_1, int dest_position_id_2, int dest_position_id_3, int sour_cluster_id , int sour_position_id_0, int sour_position_id_1,int sour_position_id_2,int sour_position_id_3);
static int setup_routing_computation();

void agg_setup_gen();

void pk_setup_arr_actions(Packet* pkptr, int instrm);


void exter_rolling_check();
void exter_tear_chose_to_send(int list_len_mid,int i);
void exter_ack_chose_to_send(int list_len_mid, int i);
void exter_setup_chose_to_send(int list_mid , int i);

void exter_control_switch();

static void pk_teardown_arr_actions(Packet* pkptr,int instrm);

static void pk_ack_arr_actions(Packet* pkptr, int strm);

static void local_pk_optical_send(int list_len_send);

static void pk_exter_opc_arr_actions(Packet* pkptr, int instrm);

static void opc_st_free(Ici* ici_opc_st_free);








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
	PORT_INFO *	            		port_info                                       ;
	Objid	                  		own_objid                                       ;
	Objid	                  		node_objid                                      ;
	double	                 		packet_setup_length                             ;
	double	                 		packet_data_length                              ;
	double	                 		transmission_bandwidth_ele                      ;
	double	                 		packet_ack_length                               ;
	double	                 		packet_teardown_length                          ;
	int	                    		local_group_id                                  ;
	int	                    		local_switch_id                                 ;
	int	                    		local_server_id                                 ;
	double	                 		transmission_bandwidth_opc                      ;
	int	                    		port_num                                        ;
	List*	                  		lptr_elec_candidate_info[5]                     ;
	List*	                  		lptr_elec_routing_trace_info                    ;
	Stathandle	             		stat_conf_handle                                ;
	int	                    		stat_conf_count                                 ;
	int	                    		stat_buf_count                                  ;
	Stathandle	             		stat_buf_handle                                 ;
	} Oars_Switch_state;

#define port_info               		op_sv_ptr->port_info
#define own_objid               		op_sv_ptr->own_objid
#define node_objid              		op_sv_ptr->node_objid
#define packet_setup_length     		op_sv_ptr->packet_setup_length
#define packet_data_length      		op_sv_ptr->packet_data_length
#define transmission_bandwidth_ele		op_sv_ptr->transmission_bandwidth_ele
#define packet_ack_length       		op_sv_ptr->packet_ack_length
#define packet_teardown_length  		op_sv_ptr->packet_teardown_length
#define local_group_id          		op_sv_ptr->local_group_id
#define local_switch_id         		op_sv_ptr->local_switch_id
#define local_server_id         		op_sv_ptr->local_server_id
#define transmission_bandwidth_opc		op_sv_ptr->transmission_bandwidth_opc
#define port_num                		op_sv_ptr->port_num
#define lptr_elec_candidate_info		op_sv_ptr->lptr_elec_candidate_info
#define lptr_elec_routing_trace_info		op_sv_ptr->lptr_elec_routing_trace_info
#define stat_conf_handle        		op_sv_ptr->stat_conf_handle
#define stat_conf_count         		op_sv_ptr->stat_conf_count
#define stat_buf_count          		op_sv_ptr->stat_buf_count
#define stat_buf_handle         		op_sv_ptr->stat_buf_handle

/* These macro definitions will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE
#define FIN_PREAMBLE_DEC	Oars_Switch_state *op_sv_ptr;
#define FIN_PREAMBLE_CODE	\
		op_sv_ptr = ((Oars_Switch_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr));


/* Function Block */

#if !defined (VOSD_NO_FIN)
enum { _op_block_origin = __LINE__ + 2};
#endif


/*服务器位置上传分组以及 switch_id 为k/2至k-2号汇聚层交换机发送分组 */
static void elec_pk_arr_actions(Packet *pkptr,int instrm)
{
int  i;


FIN(elec_pk_arr_actions(pkptr,instrm));

	for(i=0;i<5;i++)//此端口数14，i<14
		{
		  if(port_info[i].instrm_index_elec == instrm)
			  {
			  
			 // printf("rx: %d, J: %d\n ", port_info[i].instrm_index_elec, instrm);
			  op_subq_pk_insert(i,pkptr,OPC_QPOS_TAIL);
			  break;
			  }
		  else
			  {
	//		  printf("pkptr: %d",op_pk_id(pkptr));
	//		  printf("rx: %d, J: %d\n ", port_info[i].instrm_index_elec, instrm);
			  //printf("error insert!\n");
			  //printf("1. %d, 2. %d\n", local_group_id, local_switch_id);
			  
			  continue;
			  }
		}
	

FOUT;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*基于分组的路由*/
static void edg_elec_routing_computation()
{
  int i=0;
  int j=0;
  Packet* pkptr = OPC_NIL;
  
//  Distribution *port_out_dist;
  int port_out          = -1;
//int dest_net_index    = -1;
  int dest_group_index  = -1;
  int dest_switch_index = -1;
//int dest_unique_index = -1;//可能加一项
  int dest_server_index = -1;
  
  CANDI_INFO_ELEC  *ptr_candidate_info = OPC_NIL;
  
  FIN(edg_elec_routing_computation())
	  
	  /*轮询边缘交换机的下行端口  端口编号 0~(k/2-1)*/
	  
	  for(i=0; i<5; i++)//端口数i<7
		  {
		  if(op_subq_empty(i)==OPC_TRUE)
			  {
			  continue;
			  }
		  else
			  {
			  
			  /*获取分组信息*/
			  pkptr = op_subq_pk_access (i, OPC_QPOS_HEAD);
		//	  op_pk_fd_get(pkptr, DEST_NET_INDEX, &dest_net_index );
		//	  op_pk_fd_get(pkptr, DEST_POD_INDEX, &dest_pod_index );
			  
			  op_pk_fd_get(pkptr, DEST_GROUP_INDEX, &dest_group_index);//可能加一项
			  op_pk_fd_get(pkptr, DEST_SWITCH_INDEX, &dest_switch_index);
			  op_pk_fd_get(pkptr, DEST_SERVER_INDEX, &dest_server_index );
			  
			 		
		//	  M = (dest_switch_index % 4) - (local_switch_id % 4);//如何确定上行端口
			  
			  /*case 1: 本地流量，直接发往目的地址 */
			  
		//	  printf("1. %d, 2. %d, 3. %d\n", local_group_id, local_switch_id, local_server_id );
			  
			 if(dest_group_index == local_group_id && dest_switch_index == local_switch_id)
				  {
				  port_out = dest_server_index;
				  }
			  
			 else if(dest_group_index == local_group_id && dest_switch_index != local_switch_id)
				  {
		//		  port_out_dist = op_dist_load("uniform_int", 2, 3);
		//		  port_out      = op_dist_outcome(port_out_dist);
				  port_out = dest_switch_index;
		//		  op_dist_unload(port_out_dist);
				  }
			  
			 else if(dest_group_index != local_group_id)
				  {
				  port_out = 4;
				  }
			  
			 else
				  {
                  printf("error in the routing algorithm in the inter-server switch!\n ");
				  }
			  
			  
			  ptr_candidate_info = (CANDI_INFO_ELEC*)op_prg_mem_alloc(sizeof(CANDI_INFO_ELEC));
			  ptr_candidate_info-> subq_in_elec = i ;
			  ptr_candidate_info-> port_out_elec = port_out;
			
			  op_prg_list_insert(lptr_elec_candidate_info[port_out],ptr_candidate_info, OPC_LISTPOS_TAIL);
			  
			  
			  }
		  
		  
		  
		  
		  }
  
  
  
  /*轮询交换机上行端口队列  端口编号 k/2~(k-1)*/
  /*3.22
       for(i=7; i<14; i++)//上行端口7-13
		   {
		    if(op_subq_empty(i)==OPC_TRUE)
			    {
			       continue;
			    }
			else
				{
				 /*获取分组信息*/
	/*3.22		       pkptr = op_subq_pk_access (i, OPC_QPOS_HEAD);
			       
			       op_pk_fd_get(pkptr, DEST_SERVER_INDEX, &dest_server_index);
				   
				   port_out = dest_server_index-2;
				   
				   
			  /*写入申请输出列表*/
			  
	/*3.22		      ptr_candidate_info = (CANDI_INFO_ELEC*)op_prg_mem_alloc(sizeof(CANDI_INFO_ELEC));
			      ptr_candidate_info-> subq_in_elec = i ;
			      ptr_candidate_info-> port_out_elec = port_out;
			
			      op_prg_list_insert(lptr_elec_candidate_info[port_out],ptr_candidate_info, OPC_LISTPOS_TAIL); 
			   
				   
				   
				   
				   }
			}
	 3.22*/  
	   
	   FOUT;
  
  
  
 }



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*基于分组的转发*/
static void edg_elec_candidate_chose_to_send(int list_len ,int i)
	
{
int j;
Distribution *num_chose_dist;
int num_chose;
Packet *pkptr;
//int flow_num_temp;
//int pk_position_temp;
	
///int list_routing_trace;

//int k;

double transmission_bandwidth;


CANDI_INFO_ELEC *ptr_candidate_info ;



FIN(edg_elec_candidate_chose_to_send());



/* 产生随机数 */
num_chose_dist = op_dist_load("uniform_int", 1, list_len);

num_chose = op_dist_outcome(num_chose_dist);

j=num_chose -1;

op_dist_unload(num_chose_dist);

ptr_candidate_info = (CANDI_INFO_ELEC*) op_prg_list_access(lptr_elec_candidate_info[i],j);

pkptr=op_subq_pk_remove(ptr_candidate_info->subq_in_elec, OPC_QPOS_HEAD);


if(i == 4)
	{
	transmission_bandwidth = 3*transmission_bandwidth_opc;
	}
else
	{
	transmission_bandwidth = transmission_bandwidth_ele;
	}


op_pk_send_delayed(pkptr,port_info[ptr_candidate_info->port_out_elec].outstrm_index_elec, packet_data_length/transmission_bandwidth);

FOUT;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*基于流的路由*/
/*
static void edg_elec_routing_computation()
{
int i;
int j;
Packet * pkptr;
int flow_pk_position_t;
int flow_num_temp ;

Distribution *portout_dist ;
ROUTE_MOU_FLOW *ptr_route_info ;
CANDI_INFO_ELEC *ptr_candidate_info ;

int portout_t;
int list_len_routing;

int dest_pod_index;
int dest_switch_index;
int dest_unique_index;

int pkt_buf_num=0;


int list_len_test=0;

FIN(edg_elec_routing_computation())
	
	
	
	 
	/*debug*/
	/*
	
	printf("function: edg_elec_routing_computation()\n ");
	printf("local node address:(%d,%d,%d,%d)\n", local_net_id, local_pod_id, local_switch_id,local_unique_id);
	for(i=0;i<port_num;i++)
		{
		list_len_test = op_prg_list_size(lptr_elec_candidate_info[i]);
		
		
	    printf("output port: %d\n", i);
	    printf("list len:           %d   \n",list_len_test);
		
		
		}
	printf("function finished  !\n ");
	*/
	
	
/*统计交换机中存储的分组总数，写入统计变量*/

/*
for(i=0;i<port_num;i++)
	{
	pkt_buf_num=pkt_buf_num+op_subq_stat(i,OPC_QSTAT_PKSIZE);
	}

/*写入统计数据*/

/*
    op_stat_write(stat_buf_handle, pkt_buf_num);

	
	

/*轮询服务器方向的下行端口 队列号：0~(k/2-1)*/

/*
	
for(i=0;i<port_num/2; i++)
	{
	if(op_subq_empty(i)==OPC_TRUE)
		{
		continue;
		}
	
	/* 计算输出端口，写入申请列表中 */

/*
	else
		{
		/*若为一条数据流的头部分组，则随机选择上行输出端口，并将路由结果记录在 lptr_elec_routing_trace_info 中*/

/*
		pkptr = op_subq_pk_access(i,OPC_QPOS_HEAD);
		op_pk_fd_get(pkptr,FLOW_PK_POS,&flow_pk_position_t);
		op_pk_fd_get(pkptr, FLOW_NO ,&flow_num_temp);
		op_pk_fd_get(pkptr, DEST_POD_INDEX,& dest_pod_index);
		op_pk_fd_get(pkptr, DEST_SWITCH_INDEX, &dest_switch_index);
		op_pk_fd_get(pkptr, DEST_UNIQUE_INDEX, &dest_unique_index);
		
		
		/* case 1: 本地流量，直接转发至目的服务器 */
/*
		if(dest_pod_index ==local_pod_id && dest_switch_index == local_switch_id)
			{
			portout_t = dest_unique_index-2 ;
			}
		
		
		/*case 2: 发往pod内或pod间流量，流头随机转发，流内其他分组按照流表转发 */
/*		else
			{
		
		      if(flow_pk_position_t == FLOW_HEAD)
			    {
			     portout_dist = op_dist_load("uniform_int", port_num/2, port_num-1);
			
			     portout_t = op_dist_outcome(portout_dist);
			
			     op_dist_unload(portout_dist);
			     }
	     /*根据列表查询输出端口 */
/*		      else
			    {
			
			     list_len_routing = op_prg_list_size(lptr_elec_routing_trace_info);
			
			      for(j=0;j<list_len_routing;j++)
				     {
				      ptr_route_info=(ROUTE_MOU_FLOW*)op_prg_list_access(lptr_elec_routing_trace_info,j);
				
				      if(ptr_route_info->flow_num_info == flow_num_temp);
				        {
				         portout_t= ptr_route_info-> port_out_info;
				         break;
				        }
				     }
							
				 }
			  }
		
		/* 写入申请列表 */
			
/*			ptr_candidate_info = (CANDI_INFO_ELEC*)op_prg_mem_alloc(sizeof(CANDI_INFO_ELEC));
			ptr_candidate_info-> subq_in_elec = i ;
			ptr_candidate_info-> port_out_elec = portout_t;
			
			op_prg_list_insert(lptr_elec_candidate_info[portout_t],ptr_candidate_info, OPC_LISTPOS_TAIL);
			
			/*
			printf("****************************edg_elec_candidate_rolling*************************\n");
	        printf("local node address:(%d,%d,%d,%d)\n", local_net_id, local_pod_id, local_switch_id,local_unique_id);
	        printf("output port: %d\n", portout_t);
			printf("a candidate has been inserted!\n");
			*/
		
/*			}
	
	}

/*轮询 k/2 至 (k/2-1) 号队列 上行端口到达的分组，目的输出端口为下行服务器的端口，唯一确定*/

/*    for(i=port_num/2;i<port_num;i++)
		{
		if(op_subq_empty(i)==OPC_TRUE)
			{
			continue;
			}
		else
			{
			  
			  pkptr = op_subq_pk_access(i,OPC_QPOS_HEAD);
			  
			  op_pk_fd_get(pkptr, DEST_UNIQUE_INDEX , & dest_unique_index);
			  
			  portout_t = dest_unique_index -2;
			  
			  /*写入申请列表中*/
/*			  ptr_candidate_info = (CANDI_INFO_ELEC*) op_prg_mem_alloc(sizeof(CANDI_INFO_ELEC));
			  ptr_candidate_info->subq_in_elec = i;
			  ptr_candidate_info->port_out_elec = portout_t;
			  op_prg_list_insert(lptr_elec_candidate_info[portout_t],ptr_candidate_info, OPC_LISTPOS_TAIL);
			  
			/*
			printf("****************************edg_elec_candidate_rolling*************************\n");
	        printf("local node address:(%d,%d,%d,%d)\n", local_net_id, local_pod_id, local_switch_id,local_unique_id);
	        printf("output port: %d\n", portout_t);
			printf("a candidate has been inserted!\n");
			*/
/*			
			  }
		}
	
	
	
	
	
	
	
	
	
	
	FOUT;


}
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*基于流的转发*/
/*
static void edg_elec_candidate_chose_to_send(int list_len ,int i)
	
{
int j;
Distribution *num_chose_dist;
int num_chose;
Packet *pkptr;
int flow_num_temp;
int pk_position_temp;
	
int list_routing_trace;

int k;



CANDI_INFO_ELEC *ptr_candidate_info ;
ROUTE_MOU_FLOW  *ptr_routing_flow_info;


FIN(edg_elec_candidate_chose_to_send());


/* 统计网络中流量的冲突 */
/*
if(list_len!=1)
	{
	stat_conf_count = stat_conf_count +(list_len-1);
///	printf("%d\n",stat_conf_count);
	}

/* 产生随机数 */
/*
num_chose_dist = op_dist_load("uniform_int", 1, list_len);

num_chose = op_dist_outcome(num_chose_dist);

j=num_chose -1;

op_dist_unload(num_chose_dist);

ptr_candidate_info = (CANDI_INFO_ELEC*) op_prg_list_access(lptr_elec_candidate_info[i],j);

pkptr=op_subq_pk_remove(ptr_candidate_info->subq_in_elec, OPC_QPOS_HEAD);


/* 上行流量：需要记录输出端口号 或者删除路由信息 */
/*
if(i>port_num/2-1)
	{
	
	/*数据流的头部 则需要记录上行端口号 */
/*
	op_pk_fd_get(pkptr, FLOW_NO ,&flow_num_temp);
	op_pk_fd_get(pkptr, FLOW_PK_POS ,& pk_position_temp);
	
	if(pk_position_temp == FLOW_HEAD)
		{
		/* debug */
		/*
		printf("\n****************************FLOW HEAD*****************************************\n");
		printf("ADDRESS : (%d,%d,%d,%d)\n",local_net_id ,local_pod_id, local_switch_id,local_unique_id);
		printf("flow num :  %d \n", flow_num_temp);
		printf("port out  : %d\n" , i);
		printf("**********************************TRACE RECORD *********************************\n");*/	
/*		
		ptr_routing_flow_info = (ROUTE_MOU_FLOW*)op_prg_mem_alloc(sizeof(ROUTE_MOU_FLOW));
		
		ptr_routing_flow_info->flow_num_info = flow_num_temp ;
		ptr_routing_flow_info->port_out_info = i;
		
		op_prg_list_insert(lptr_elec_routing_trace_info, ptr_routing_flow_info,OPC_LISTPOS_TAIL);
		}
	
	/*数据流的尾部： 删除路由信息 */
/*
	else if(pk_position_temp == FLOW_TAIL)
		{
		/* debug */
		/*
		/* debug */
		
/*		
		list_routing_trace = op_prg_list_size(lptr_elec_routing_trace_info);
		
		for(k=0;k<list_routing_trace;k++)
			{
			ptr_routing_flow_info =op_prg_list_access(lptr_elec_routing_trace_info,k);
						
			if(ptr_routing_flow_info->flow_num_info ==flow_num_temp)
				{
				op_prg_list_remove(lptr_elec_routing_trace_info,k);
		
				/* DEBUG */
		/*printf("\n****************************FLOW TAIL*****************************************\n");
		printf("ADDRESS : (%d,%d,%d,%d)\n",local_net_id ,local_pod_id, local_switch_id,local_unique_id);
		printf("flow num :  %d \n", flow_num_temp);
		printf("port out  : %d\n" , i);
		printf("**********************************TRACE DELET *********************************\n");*/
				
/*				break;				
				}
			
				
			}
		
		
		}
	/*
	else
		{
	
	    printf("ADDRESS : (%d,%d,%d,%d)\n",local_net_id ,local_pod_id, local_switch_id,local_unique_id);
		printf("FLOW BODY \n");
		printf("flow num :  %d \n", flow_num_temp);
		printf("port out  : %d\n" , i);
		}
	*/
	
/*	}

op_pk_send_delayed(pkptr,port_info[ptr_candidate_info->port_out_elec].outstrm_index_elec, packet_data_length/transmission_bandwidth_ele);

//op_pk_send(pkptr,port_info[ptr_candidate_info->port_out_elec].outstrm_index_elec);

FOUT;
}

*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void edg_elec_candidate_rolling()
{
int i;
int list_len_candi;

FIN(edg_elec_candidate_rolling());

for(i=0;i<5;i++)//i<14
	{
	list_len_candi = op_prg_list_size(lptr_elec_candidate_info[i]);
	
	/*debug*/
	/*
	printf("****************************edg_elec_candidate_rolling*************************\n");
	printf("local node address:(%d,%d,%d,%d)\n", local_net_id, local_pod_id, local_switch_id,local_unique_id);
	printf("output port: %d\n", i);
	printf("list len:           %d   \n",list_len_candi);
	*/
	
	
	if(list_len_candi ==0)
		{
		continue;
		}
	else
		{
		edg_elec_candidate_chose_to_send(list_len_candi,i);
		
		}
	
	}

FOUT;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void edg_elec_candidate_list_empty()
{
int i;

FIN(edg_elec_candidate_list_empty());

for(i=0; i<5; i++)//i<14
	{
	op_prg_list_free(lptr_elec_candidate_info[i]);
	
	}
FOUT;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*发送拆链分组， 解锁边缘交换机 7号端口的对应队列 */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*到达目的接入交换机的数据分组，存入汇聚队列中 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*到达源接入交换机的ack 分组，按照ACK分组预约波长存入ACK 队列中  */
/////////////////////////////////////////////////////////////////////////////////////////////////

/*到达源接入交换机的 nack 分组，将对应队列的AGG_SETUP_GEN 重新置0以重新产生建链分组 */




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*到达目的接入交换机的拆链分组，销毁该拆链分组 */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////












	


	
	



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
   
           /*若队列中的分组已经发送完毕 ，则产生拆链分组，将拆链分组置入队列 TEARDOWN_SUBQ_BEGIN */
       /*
		if(op_subq_empty(opc_subq_num_temp)==OPC_TRUE)
	       {
	         pkptr_tear =op_pk_create(packet_teardown_length);
	   
	         op_pk_encap_flag_set(pkptr_tear, OPC_TEARDOWN_FLAG);
	
	         op_pk_fd_set(pkptr_tear, ID_NO_OPC_FLOW,OPC_FIELD_TYPE_INTEGER, opc_flow_num_temp, 15);
	         op_pk_fd_set(pkptr_tear, WAVE_NUM      ,OPC_FIELD_TYPE_INTEGER,  wave_num_temp   ,   3);
	
	         /*写入源地址和目的地址 */
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
	   
	          /* 记录该条目的位置，准备删除该条目 */
			 
	   /*
	         item_del_flow_num = (int*)op_prg_mem_alloc(sizeof(int));
			 *item_del_flow_num = opc_flow_num_temp ;
	         op_prg_list_insert(lptr_item_del_info,item_del_flow_num ,OPC_LISTPOS_TAIL);
	    
			 }
		
   
       
       /*若队列不为空，从队列的头部提取分组，修改分组的流号，发送该分组；2。锁住输出端口 OPC_ST_PORT_LOCK,创建ICI信息，在下一个轮询周期之前解锁输出端口 */
       
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
			 
			 /*绑定 ICI */
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
   		
   
         /*根据 lptr_item_del_info 中记录的数据删除 lptr_local_traffic_send_info 中的数据 */
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
   
   
           /*清空 lptr_item_del_info 中的信息 */
   /*
            op_prg_list_free(lptr_item_del_info);
			
  
   FOUT;
	
}


////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////
/* 轮询汇聚队列 ：AGG_QUEUE_SEND_BEGIN 开始，共96条队列，查询队列中是否已经产生建链分组，若尚未产生建链分组，则需要产生建链分组注入本地建链分组队列*/
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
			/* 尚未产生建链分组，产生建链分组并将旗量置1，随后将建链分组插入相应的队列中 */
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
			
			/* 根据源地址以及目的地址确定通信使用的波长序号 */
//			wave_allot = wave_allocation(dest_cluster_id,dest_position_id_0,dest_position_id_1,dest_position_id_2,dest_position_id_3,sour_cluster_id ,sour_position_id_0,sour_position_id_1,sour_position_id_2,sour_position_id_3);
			
			
			
			/* 产生建链分组 */
			
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
			
			/* 根据路由函数计算输出端口 */
//			port_out_setup = setup_routing_computation(dest_position_id_0, dest_position_id_1,dest_position_id_2,dest_position_id_3 ,dest_cluster_id);
						
			/* 写入信息记录列表 */
			
/*			ptr_local_setup_info = (LOCAL_SETUP_INFO*)op_prg_mem_alloc(sizeof(LOCAL_SETUP_INFO));
			
			ptr_local_setup_info->opc_flow_num_rec  = opc_flow_num ;
			ptr_local_setup_info->opc_data_subq_rec = i;
			ptr_local_setup_info->port_out_rec      = port_out_setup;
			ptr_local_setup_info->wave_num_rec      = wave_allot    ;
			op_prg_list_insert(lptr_local_setup_info,ptr_local_setup_info,OPC_LISTPOS_TAIL);
			
				
			/*将建链分组插入相应的队列中 */
/*		    local_setup_subq_in = LOCAL_SETUP_SEND_BEGIN + port_out_setup*15+wave_allot;
			
			op_subq_pk_insert(local_setup_subq_in,pkptr_setup, OPC_QPOS_TAIL);
			
			/*更新相关信息*/
			
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
  
 
   
  
	
	/* 轮询 待转发队列中的建链分组 */
  
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
				/*  记录分组的相关信息 */
		/*		ptr_setup_candi_info = (EXTER_CANDI_INFO*)op_prg_mem_alloc(sizeof(EXTER_CANDI_INFO));
				ptr_setup_candi_info->opc_flow_num_cd = flow_num_temp;
			    ptr_setup_candi_info->subq_in_cd = i;
				ptr_setup_candi_info->port_out_cd = port_out_temp;
				ptr_setup_candi_info->wave_num_cd = wave_num_temp;
				
				op_prg_list_insert(lptr_exter_setup_candidate_info[port_out_temp],ptr_setup_candi_info,OPC_LISTPOS_TAIL);							
				
				}
						
			
			}
		
		
		} /* 结束对于待转发 建链分组的轮询 */
  
  /*轮询本地端口的建链分组队列 因为本地建链分组的发送不用记录在 lptr_exter_traffic_info 中，所以申请的信息栏中只用保留信息 子队列号，输出端口号，波长号*/
/*  for(i=LOCAL_SETUP_SEND_BEGIN;i<LOCAL_SETUP_SEND_BEGIN+90;i++)
	  {
	  if(op_subq_empty(i)==OPC_TRUE)
		  {
		  continue;
		  }
	  else
		  {
		  /*计算本地建链分组的目的输出端口  以及 所预约的波长 */
	/*	  port_out_temp = (i - LOCAL_SETUP_SEND_BEGIN)/15;
		  wave_num_temp = (i - LOCAL_SETUP_SEND_BEGIN)%15;
		  
		  pkptr=op_subq_pk_access(i,OPC_QPOS_HEAD);
		  
		  op_pk_fd_get(pkptr, ID_NO_OPC_FLOW, &flow_num_temp);
		  
		  
		  /*写入申请列表 */
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
  
  /*对于6个输入端口的ack分组进行轮询 */
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
		  
		  
		  /*在踪迹列表中查询ACK分组的输入端口 */
/*		  list_len = op_prg_list_size(lptr_exter_traffic_trace_info);
		  
		  for(j=0;j<list_len;j++)
			  {
			  ptr_trace_info = (TRACE_INFO*)op_prg_list_access(lptr_exter_traffic_trace_info,j);
			  if(ptr_trace_info->flow_opc_num_info == flow_num_temp)
				  {
				  port_out_temp = ptr_trace_info->port_in_info;
				  break;
				  }  
			  
			  }/* 结束对于输出端口的查询 */
		
		  /* 写入对应输出端口的申请列表 */
	/*	  ptr_ack_candi_info = (EXTER_CANDI_INFO*)op_prg_mem_alloc(sizeof(EXTER_CANDI_INFO));
		  ptr_ack_candi_info->subq_in_cd = i;
		  ptr_ack_candi_info->port_out_cd= port_out_temp;
		  op_prg_list_insert(lptr_exter_ack_candidate_info[port_out_temp],ptr_ack_candi_info,OPC_LISTPOS_TAIL);
		  }
	  }/* 结束对于ACK分组队列的轮询 */
		  
/* 结束对于ACK分组的轮询处理 */
  
/*对于等待转发的拆链分组的处理，队列存储规则：BEGIN 为本地的拆链分组队列 ；随后的6条队列分别存储的是6个方向的端口上的分组 */
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
		  
		  /*由于本地建链分组的相关信息记录在 lptr_local_setup_info 中，转发建链分组的信息记录 在  lptr_exter_traffic_info 中*/
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
		  
		  /*写入相应端口的申请列表 lptr_exter_teardown_candidate_info */
/*		  ptr_tear_candi_info = (EXTER_CANDI_INFO*)op_prg_mem_alloc(sizeof(EXTER_CANDI_INFO));
		  
		  ptr_tear_candi_info->opc_flow_num_cd = flow_num_temp;
		  ptr_tear_candi_info->subq_in_cd = i;
		  ptr_tear_candi_info->port_out_cd = port_out_temp;
		  ptr_tear_candi_info->wave_num_cd = wave_num_temp;
		  op_prg_list_insert(lptr_exter_teardown_candidate_info[port_out_temp],ptr_tear_candi_info,OPC_LISTPOS_TAIL);
		  
		  
		  
		  
		  }
	  
	  }/* 结束对于拆链分组队列的轮询 */
  
/*  
FOUT;
	
  }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*选择拆链分组发送，若拆链分组为本地拆链分组：队列号为 TEARDOWN_SUBQ_BEGIN ,则根据流号 删除本地列表 lptr_local_setup_info 中的信息； 否则，删除 lptr_exter_traffic_trace_info 中的信息 */
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
	
	
	/*拆链分组为本地拆链分组 , 1 删除 lptr_local_setup_info 中的相关条目 2 解锁输出端口的对应波长 3 解锁建链分组的产生标记 SETUP_GEN_FLAG */
	
/*	if(subq_in_temp == TEARDOWN_SUBQ_BEGIN)
		{
		pkptr = op_subq_pk_remove(subq_in_temp,OPC_QPOS_HEAD);
		
		/* 发送拆链分组 */
/*		op_pk_send_delayed(pkptr,port_exter_rack[portout_temp].outstrm_setup_index,packet_teardown_length/(transmission_bandwidth*10000000));
		
		
	    /*1 删除列表 lptr_local_setup_info 中的相关信息 2 解锁输出端口   */
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
	
/*否则，拆链分组非本地的拆链分组，1 将trace 信息从 lptr_exter_traffic_trace_info 中删除 ; 2 解锁输出端口的对应波长 */

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
/*选择相应队列的ACK分组并发送该分组，不用做后续的处理工作 */
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
		
		/* 发送该建链分组 */
		
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
/*对于 setup 分组的处理 ： 1 发送分组 2 将分组信息写入列表 3 标记输出端口的相应波长占用 */
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
	
	
	/*本地建链分组的信息记录在 lptr_local_setup_info 中 */
/*	if(subq_in_temp>LOCAL_SETUP_SEND_BEGIN -1 && subq_in_temp <LOCAL_SETUP_SEND_BEGIN+90)
		{
		pkptr = op_subq_pk_remove(subq_in_temp, OPC_QPOS_HEAD);
		
		/* 标记输出端口的 波长占用*/
		
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
	
	/*待转发建链分组，需要记录信息，标记输出端口的对应波长为占用状态*/
	
/*	else
		{
		/* 根据队列号计算输入端口号 */
/*		port_in_temp =(subq_in_temp-SETUP_EXTER_SUBQ_BEGIN)/15;
		
		/*将建链分组的相关信息记录到 lptr_exter_traffic_trace_info 中 */
		
/*		pkptr = op_subq_pk_remove(subq_in_temp,OPC_QPOS_HEAD);
		
		ptr_setup_trace_info=(TRACE_INFO*)op_prg_mem_alloc(sizeof(TRACE_INFO));
		
		ptr_setup_trace_info->flow_opc_num_info = opc_flow_num_temp;
		ptr_setup_trace_info->port_in_info      = port_in_temp     ;
		ptr_setup_trace_info->port_out_info     = port_out_temp    ;
		ptr_setup_trace_info->wave_num_info     = wave_num_temp    ;
		
		op_prg_list_insert(lptr_exter_traffic_trace_info, ptr_setup_trace_info, OPC_LISTPOS_TAIL);
		
		/*标记输出端口*/
/*		PORT_WAVE_LOCK[port_out_temp][wave_num_temp]=1;
		
				
		op_pk_send_delayed(pkptr, port_exter_rack[port_out_temp].outstrm_setup_index, packet_setup_length/(transmission_bandwidth*10000000));
		
		/* debug */
		/*
		printf("**********************ATTENTION***********************\n");
	    printf("op_sim_time (us) : %f\n",op_sim_time()*1000000);
	    printf("setup packet is sent from node (%d,%d%d%d%d) \n",local_cluster_id,local_position_id[3],local_position_id[2],local_position_id[1],local_position_id[0]);
		printf("PORT_WAVE_LOCK[%d][%d]: %d  \n",port_out_temp,wave_num_temp,PORT_WAVE_LOCK[port_out_temp][wave_num_temp]);
	   	*/
	
		
/*		}/*建链分组处理完毕 */
	
/*	FOUT;
	

	
	
	
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*对于lptr_exter_setup_candidate_info 以及 lptr_exter_ack_candidate_info 作出仲裁，设定分组的优先级顺序设置为拆链分组，ack 分组，setup 分组 */
/*
void exter_control_switch()
{

int portout_occupy_flag[6] ={-1,-1,-1,-1,-1,-1};

int ack_list_len     =-1;
int setup_list_len   =-1;
int tear_list_len    =-1;

int i = -1;



FIN(exter_control_switch());

/*首先处理teardown 分组，若lptr_exter_teardown_candidate_info 不为空，则必然能够选择其中一个拆分组发送，后续不再处理该端口的其他分组 */
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
	
	
	}/* 对拆链分组的处理结束 */


/*处理ack 分组，若lptr_exter_ack_candidate_info 不为空，则必然能够选择ack分组发送 */

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
	}/*对ACK分组的处理结束 */

/*其次处理 建链分组 */
/*对于建链分组包括以下处理步骤 ：*/
/*1 标记对应输出端口的对应波长占用 2 记录建链分组的trace */
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

/* 处理6个端口的待转发 拆链分组 */
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

/* 到达目的节点的拆链分组，销毁拆链分组  */
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

/*否则，将拆链分组存储至相应的队列中等待发送 */
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

/* 处理中间转发的setup 分组以及到达目的节点（rack）的 SETUP 分组 */
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



/*到达目的节点的 setup 分组 ，产生 ACK 分组并反向传输 */
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
	
	/*产生ACK 分组 */
/*	pkptr_ack =op_pk_create(packet_ack_length);
	
	op_pk_encap_flag_set(pkptr_ack, OPC_ACK_FLAG);
	
	op_pk_fd_set(pkptr_ack, ID_NO_OPC_FLOW,OPC_FIELD_TYPE_INTEGER, opc_flow_num, 15);
	op_pk_fd_set(pkptr_ack, WAVE_NUM    ,OPC_FIELD_TYPE_INTEGER,  wave_num    ,   3);
	
	/*写入源地址和目的地址 */
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
	
	/*销毁 SETUP 分组 */
	/*op_pk_destroy(pkptr);
	
	/*反向 发送 ack 分组 */
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

/*中间节点的 建链分组 将建链分组存在对应输入端口的队列中，但需要按照不同波长分别存储在不同的队列中 */
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

/*  处理 6 个端口待转发的 ACK分组  */
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


/*到达源RACK的 ACK分组，根据流号查询数据分组的队列，发送该队列中的数据分组 */
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
	
	
	
	/*根据流号查询 lptr_local_setup_info ,将相关的信息写入 lptr_lcoal_traffic_send_info 中 */
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
	
	
	/*销毁ACK 分组 */
	
/*	
	op_pk_destroy(pkptr);
	
	op_intrpt_schedule_self(op_sim_time(),Local_Agg_Traffic_Send_Rolling);
	
	
	}
/*中间节点的ACK 分组，将ACK分组存储在相应的输入端口位置 */
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
   
           /*若队列中的分组已经发送完毕 ，则产生拆链分组，将拆链分组置入队列 TEARDOWN_SUBQ_BEGIN */
       /*
		if(op_subq_empty(opc_subq_num_temp)==OPC_TRUE)
	       {
	         pkptr_tear =op_pk_create(packet_teardown_length);
	   
	         op_pk_encap_flag_set(pkptr_tear, OPC_TEARDOWN_FLAG);
	
	         op_pk_fd_set(pkptr_tear, ID_NO_OPC_FLOW,OPC_FIELD_TYPE_INTEGER, opc_flow_num_temp, 15);
	         op_pk_fd_set(pkptr_tear, WAVE_NUM      ,OPC_FIELD_TYPE_INTEGER,  wave_num_temp   ,   3);
	
	         /*写入源地址和目的地址 */
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
	   
	          /* 记录该条目的位置，准备删除该条目 */
			 
	   /*
	         item_del_flow_num = (int*)op_prg_mem_alloc(sizeof(int));
			 *item_del_flow_num = opc_flow_num_temp ;
	         op_prg_list_insert(lptr_item_del_info,item_del_flow_num ,OPC_LISTPOS_TAIL);
	    
			 }
		
   
       
       /*若队列不为空，从队列的头部提取分组，修改分组的流号，发送该分组；2。锁住输出端口 OPC_ST_PORT_LOCK,创建ICI信息，在下一个轮询周期之前解锁输出端口 */
       
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
			 
			 /*绑定 ICI */
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
   		
   
         /*根据 lptr_item_del_info 中记录的数据删除 lptr_local_traffic_send_info 中的数据 */
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
   
   
           /*清空 lptr_item_del_info 中的信息 */
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

/* 若光分组已经到达目的节点，则存储在流量汇聚接收队列中 */
   
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

/*若光分组所到达的节点为中间节点 ，则根据分组的流号查询 lptr_exter_traffic_trace_info ，然后根据相应的输出端口和波长序号转发该光分组 */
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
	void Oars_Switch (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Obtype _op_Oars_Switch_init (int * init_block_ptr);
	void _op_Oars_Switch_diag (OP_SIM_CONTEXT_ARG_OPT);
	void _op_Oars_Switch_terminate (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Address _op_Oars_Switch_alloc (VosT_Obtype, int);
	void _op_Oars_Switch_svar (void *, const char *, void **);


#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
Oars_Switch (OP_SIM_CONTEXT_ARG_OPT)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	FIN_MT (Oars_Switch ());

		{
		/* Temporary Variables */
		Packet          *pkptr    = OPC_NIL;
		int              i        =0;       
		Objid            server_objid = OPC_NIL;
		Objid            rx_strm_objid =OPC_NIL ;
		Objid            tx_strm_objid  =OPC_NIL;
		int              rx_strm_index =OPC_NIL ;
		int              tx_strm_index=OPC_NIL;
		int              server_num_temp=OPC_NIL;
		int              instrm = OPC_NIL;
		
		
		
		Objid            rx_strm_objid_elec =OPC_NIL ;
		Objid            rx_strm_objid_opc_0 =OPC_NIL ;
		Objid            rx_strm_objid_opc_1 =OPC_NIL;
		Objid            rx_strm_objid_opc_2 =OPC_NIL  ;
		Objid            rx_strm_objid_opc_3 =OPC_NIL;//可能要加波长
		
		
		int              rx_strm_index_elec =OPC_NIL ;
		int              rx_strm_index_opc_0 =OPC_NIL ;
		int              rx_strm_index_opc_1 =OPC_NIL ;
		int              rx_strm_index_opc_2 =OPC_NIL ;
		int              rx_strm_index_opc_3=OPC_NIL  ;//可能要加波长
		
		
		Objid            tx_strm_objid_elec=OPC_NIL  ;
		Objid            tx_strm_objid_opc_0=OPC_NIL;
		Objid            tx_strm_objid_opc_1 =OPC_NIL ;
		Objid            tx_strm_objid_opc_2 =OPC_NIL ;
		Objid            tx_strm_objid_opc_3 =OPC_NIL ;//可能要加波长
		
		
		
		int              tx_strm_index_elec  =OPC_NIL ;
		int              tx_strm_index_opc_0 =OPC_NIL ; 
		int              tx_strm_index_opc_1 =OPC_NIL  ;
		int              tx_strm_index_opc_2 =OPC_NIL  ; 
		int              tx_strm_index_opc_3  =OPC_NIL ;//可能要加波长 
		
		
		
		Objid            rx_objid  = OPC_NIL ;
		
		
		Objid            link_objid = OPC_NIL ;
		Objid            remote_tx_objid=OPC_NIL ;
		Objid            remote_node_objid=OPC_NIL ;
		
		//int              remote_net_index=0;
		int              remote_group_index=0;
		int              remote_switch_index=0;
		//int              remote_unique_index=0;
		int              remote_server_index=0;//可能加一项
		
		int              port_temp=0;
		//10.02
		//int port_out = -1;
		//int M=0;
		//int P=-1;
		//int Port_itemp=-1;
		//int iswitch_temp=-1;
		
		
		 Objid           tx_objid=OPC_NIL;
		
		int              j=0;
		
		
		int              list_len_send = 0 ;
		/////////////////////////////////////////////////////////
		//Ici*             ici_opc_st_free ;
		int           t=0;
		
		int             list_len_initial=0;
		/* End of Temporary Variables */


		FSM_ENTER ("Oars_Switch")

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (inital) enter executives **/
			FSM_STATE_ENTER_FORCED_NOLABEL (0, "inital", "Oars_Switch [inital enter execs]")
				FSM_PROFILE_SECTION_IN ("Oars_Switch [inital enter execs]", state0_enter_exec)
				{
				/* 得到本进程的objid */
				
				own_objid = op_id_self ();
				
				/* Get the "switch" objid   */
				node_objid= op_topo_parent(own_objid);
				
				//op_ima_obj_attr_get (node_objid, "node_net_index", &local_net_id);
				
				//printf("node_net_index%d\n", local_net_id);
				
				/*获得Position_ID 存入 4维数组中 */
				
				
				op_ima_obj_attr_get(node_objid, "node_group_index", &local_group_id);
				op_ima_obj_attr_get(node_objid, "node_switch_index", &local_switch_id);
				
				//printf("node_pod_index %d\n", local_pod_id);
				
				
				
				//printf("node_switch_index%d\n", local_switch_id);
				
				//op_ima_obj_attr_get (node_objid, "node_unique_index", &local_unique_id);////可能要加一项
				//op_ima_obj_attr_get (node_objid, "node_server_index", &local_server_id);
				
				//printf("node_unique_index%d\n", local_unique_id);
				
				
				op_ima_sim_attr_get (OPC_IMA_DOUBLE, "Setup Packet Length(bits)",&packet_setup_length);
				op_ima_sim_attr_get (OPC_IMA_DOUBLE, "Data Packet Length(bits)", &packet_data_length);
				
				
				
				op_ima_sim_attr_get (OPC_IMA_DOUBLE, "Electrical Transmission Bandwidth(bps)", &transmission_bandwidth_ele);
				op_ima_sim_attr_get (OPC_IMA_DOUBLE, "Optical Transmission Bandwidth(bps)", &transmission_bandwidth_opc);
				
				op_ima_sim_attr_get (OPC_IMA_INTEGER, "Port Number", &port_num);
				
				
				
				/*申请存储端口信息的结构体*/
				  
				port_info = (PORT_INFO*)op_prg_mem_alloc(5*sizeof(PORT_INFO));//port_num换成14
				//port_info = (PORT_INFO*)op_prg_mem_alloc(16*sizeof(PORT_INFO)) ;
				
				/*初始化 k个端口 */
				
				for(i=0;i<5;i++)
					{
					port_info[i].instrm_index_elec =-1;
					port_info[i].outstrm_index_elec =-1;
					
					}
				
				/*绑定下行方向 连接至服务器的端口 */
				/*for(i=0; i<2 ; i++)//根据端口数作适当修改i<(port_num/2 + 1)
					{
					/*查询第i 条流所绑定的 服务器 */
				/*	server_objid = op_topo_assoc(own_objid, OPC_TOPO_ASSOC_IN,OPC_OBJTYPE_QUEUE,i);
					
					rx_strm_objid = op_topo_connect(server_objid, own_objid, OPC_OBJTYPE_STRM,0);
					
					op_ima_obj_attr_get(rx_strm_objid, "dest stream",&rx_strm_index);
					
					tx_strm_objid = op_topo_connect(own_objid, server_objid,OPC_OBJTYPE_STRM,0);
					
					op_ima_obj_attr_get(tx_strm_objid, "src stream", &tx_strm_index);
					
					
					op_ima_obj_attr_get(server_objid, "node_server_index", &server_num_temp);
					
				//	printf("node_server_index_temp: %d *********", server_num_temp);
					
					/* 绑定端口 */
				/*	port_info[server_num_temp-2].instrm_index_elec = rx_strm_index;
					port_info[server_num_temp-2].outstrm_index_elec = tx_strm_index;
					
					}
				
				/* 绑定上行方向的端口 */
				for(i=0; i<5; i++)//根据端口数作适当修改i<(port_num/2 + 1)
					
					{
					
					/*第i个收信机 id */
					rx_objid = op_topo_assoc(own_objid, OPC_TOPO_ASSOC_IN, OPC_OBJTYPE_PTRX,i);
					
					/*搜索 链路的 id */
					if(op_topo_assoc(rx_objid,OPC_TOPO_ASSOC_IN,OPC_OBJTYPE_LKDUP,0) == OPC_OBJID_INVALID)
						continue;
					else		
						link_objid = op_topo_assoc(rx_objid,OPC_TOPO_ASSOC_IN,OPC_OBJTYPE_LKDUP,0);
					
					/*搜寻对端的 TX_OBJID */
				
						 remote_tx_objid =op_topo_assoc(link_objid,OPC_TOPO_ASSOC_IN,OPC_OBJTYPE_PTTX,0);
						 if(op_topo_parent(remote_tx_objid) == node_objid)
						 remote_tx_objid = op_topo_assoc(link_objid,OPC_TOPO_ASSOC_IN,OPC_OBJTYPE_PTTX,1);
					
					/* 搜所至对端 节点 */	
						 remote_node_objid = op_topo_parent(remote_tx_objid);
					
					/*获得对端节点的地址信息 */
				   //   op_ima_obj_attr_get(remote_node_objid, "node_net_index", &remote_net_index);
					    
					    op_ima_obj_attr_get(remote_node_objid, "node_switch_index", &remote_switch_index);
					
					    op_ima_obj_attr_get(remote_node_objid, "node_group_index", &remote_group_index);
				  //    op_ima_obj_attr_get(remote_node_objid, "node_server_index", &remote_server_index);//可能加一项
				   //   op_ima_obj_attr_get(remote_node_objid, "node_server_index", &remote_server_index);
					
					/* 确定上行端口的端口号 */
					
					if(local_group_id == remote_group_index && local_switch_id == remote_switch_index)
						{
						op_ima_obj_attr_get(remote_node_objid, "node_server_index", &remote_server_index);
						port_temp = remote_server_index;
						}
					else if(local_group_id == remote_group_index && local_switch_id != remote_switch_index)
						{
					    port_temp = remote_switch_index;
						}
					else if(local_group_id != remote_group_index)
						{
						port_temp = 4;
						}
					else
						{
						printf("error in the connection rules of inter-server switch!\n ");
						}
					
					/* 搜索对应的发信机 */
					tx_objid = 	op_topo_assoc(link_objid,OPC_TOPO_ASSOC_IN,OPC_OBJTYPE_PTTX,0);
					if(op_topo_parent(tx_objid) != node_objid)
					tx_objid = op_topo_assoc(link_objid,OPC_TOPO_ASSOC_IN,OPC_OBJTYPE_PTTX,1);   
					
					
					/* 绑定端口号以及输入流的流号 */
					
				
						rx_strm_objid_elec = op_topo_connect(rx_objid, own_objid, OPC_OBJTYPE_STRM , 0);
						op_ima_obj_attr_get(rx_strm_objid_elec,"dest stream", & rx_strm_index_elec);
					
					
					/*绑定端口号及输出流号*/
						
						
						tx_strm_objid_elec = op_topo_connect(own_objid, tx_objid, OPC_OBJTYPE_STRM, 0);
						op_ima_obj_attr_get(tx_strm_objid_elec, "src stream", & tx_strm_index_elec);
						
						
						
						port_info[port_temp].instrm_index_elec  = rx_strm_index_elec ;
						port_info[port_temp].outstrm_index_elec = tx_strm_index_elec ;
					
					
							
							
					}
				
				/*初始化 16 个端口的申请仲裁列表 */   //端口数修改i<7，port_num没有必要
				for(i=0;i<5;i++)
					{
					lptr_elec_candidate_info[i] = op_prg_list_create();
					}
				
				/*记录数据流路由路径列表 */
				   lptr_elec_routing_trace_info = op_prg_list_create();
				   
				   
				/*查看初始列表*/
				   
				   /*debug*/
				   /*
				   	printf("function: INITIAL\n ");
					printf("local node address:(%d,%d,%d,%d)\n", local_net_id, local_pod_id, local_switch_id,local_unique_id);
					for(i=0;i<port_num;i++)
						{
						list_len_initial = op_prg_list_size(lptr_elec_candidate_info[i]);
						
						
					    printf("output port: %d\n", i);
					    printf("list len:           %d   \n",list_len_initial);
						
						
						}
					printf("function finished  !\n ");
				  
				   */
				   
				   
					
				   /*
				   for(i=0;i<port_num;i++)
					   {
					   list_len_initial= op_prg_list_size(lptr_elec_candidate_info[i]);
				       printf("initial\n");
					   printf("port: %d\n",i);
					   printf("list_len:  %d\n",list_len_initial);
					   }
				   */
				   
				
				/*注册统计量句柄，初始化统计变量*/
				   
				stat_conf_count = 0;
				stat_conf_handle = op_stat_reg("stat_conf_local",OPC_STAT_INDEX_NONE,OPC_STAT_LOCAL);
				   
				
				/*注册统计量句柄，初始化统计变量*/
				 
				stat_buf_count = 0;
				   
				stat_buf_handle =op_stat_reg("stat_buf_local",OPC_STAT_INDEX_NONE,OPC_STAT_LOCAL);
				
				   
				
				
				op_intrpt_schedule_self(op_sim_time(),Edg_Elec_Switching);
				
				
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
				
				/* 创建用于本地仲裁的列表 */
				/*
				for(i=0;i<num_rack_servers;i++)
					{
					local_lptr_candidate_info[i] = op_prg_list_create();
					}
				
				op_intrpt_schedule_self(op_sim_time(),Rack_Internal_Switching);
				
				
				
				/* 结束端口的绑定 */
				
				/*建立 6个输出端口方向上建链分组的申请列表 */
				/*
				for(i=0;i<6;i++)
					{
					lptr_exter_setup_candidate_info[i]=op_prg_list_create();
					}
				
				
				/* 建立6个输出端口方向上的ACK分组申请列表 */
				/*
				
				for(i=0;i<6;i++)
					{
					lptr_exter_ack_candidate_info[i]=op_prg_list_create();
					}
				
				
				/*建立6 个输出端口方向上的拆链分组申请列表 */
				
				/*
				for(i=0;i<6;i++)
					{
					lptr_exter_teardown_candidate_info[i]=op_prg_list_create();
					}
				
				
				
				   
				/* 创建记录发送数据分组的信息列表 */
				 /*  
				  lptr_local_traffic_send_info = op_prg_list_create();
				   
				/*创建删除 local_traffic_send_info 中相关条目的列表 */
				   
				 // lptr_item_del_info = op_prg_list_create();
				   
				   
				/*初始化输出端口波长的锁定记录 */
				/*  
				for(i=0;i<6;i++)
					{
					for(j=0;j<15;j++)
						{
						PORT_WAVE_LOCK_TAG[i][j]=0;
						}
					}
				
				
				
				
				/* 本rack内部的分组交换 */
				/*
				op_intrpt_schedule_self(op_sim_time(),Agg_Traffic_Rolling);
				op_intrpt_schedule_self(op_sim_time(),Traffic_Exter_Switch);
				*/
				
				
				
				
				
				
				
				}
				FSM_PROFILE_SECTION_OUT (state0_enter_exec)

			/** state (inital) exit executives **/
			FSM_STATE_EXIT_FORCED (0, "inital", "Oars_Switch [inital exit execs]")


			/** state (inital) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "inital", "idle", "tr_0", "Oars_Switch [inital -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (idle) enter executives **/
			FSM_STATE_ENTER_UNFORCED (1, "idle", state1_enter_exec, "Oars_Switch [idle enter execs]")

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (3,"Oars_Switch")


			/** state (idle) exit executives **/
			FSM_STATE_EXIT_UNFORCED (1, "idle", "Oars_Switch [idle exit execs]")


			/** state (idle) transition processing **/
			FSM_PROFILE_SECTION_IN ("Oars_Switch [idle trans conditions]", state1_trans_conds)
			FSM_INIT_COND (PK_ARRIVAL)
			FSM_TEST_COND (EDG_ELEC_SWITCH)
			FSM_TEST_COND (END_SIM)
			FSM_DFLT_COND
			FSM_TEST_LOGIC ("idle")
			FSM_PROFILE_SECTION_OUT (state1_trans_conds)

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 3, state3_enter_exec, ;, "PK_ARRIVAL", "", "idle", "PK_ARRIVAL", "tr_2", "Oars_Switch [idle -> PK_ARRIVAL : PK_ARRIVAL / ]")
				FSM_CASE_TRANSIT (1, 4, state4_enter_exec, ;, "EDG_ELEC_SWITCH", "", "idle", "Edg_Eelc_Sw", "tr_3", "Oars_Switch [idle -> Edg_Eelc_Sw : EDG_ELEC_SWITCH / ]")
				FSM_CASE_TRANSIT (2, 2, state2_enter_exec, ;, "END_SIM", "", "idle", "stat_collect", "tr_5", "Oars_Switch [idle -> stat_collect : END_SIM / ]")
				FSM_CASE_TRANSIT (3, 1, state1_enter_exec, ;, "default", "", "idle", "idle", "tr_6", "Oars_Switch [idle -> idle : default / ]")
				}
				/*---------------------------------------------------------*/



			/** state (stat_collect) enter executives **/
			FSM_STATE_ENTER_UNFORCED (2, "stat_collect", state2_enter_exec, "Oars_Switch [stat_collect enter execs]")
				FSM_PROFILE_SECTION_IN ("Oars_Switch [stat_collect enter execs]", state2_enter_exec)
				{
				op_stat_write(stat_conf_handle, stat_conf_count);
				}
				FSM_PROFILE_SECTION_OUT (state2_enter_exec)

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (5,"Oars_Switch")


			/** state (stat_collect) exit executives **/
			FSM_STATE_EXIT_UNFORCED (2, "stat_collect", "Oars_Switch [stat_collect exit execs]")


			/** state (stat_collect) transition processing **/
			FSM_TRANSIT_MISSING ("stat_collect")
				/*---------------------------------------------------------*/



			/** state (PK_ARRIVAL) enter executives **/
			FSM_STATE_ENTER_FORCED (3, "PK_ARRIVAL", state3_enter_exec, "Oars_Switch [PK_ARRIVAL enter execs]")
				FSM_PROFILE_SECTION_IN ("Oars_Switch [PK_ARRIVAL enter execs]", state3_enter_exec)
				{
				//printf("PK ARRIVE\n");
				
				instrm = op_intrpt_strm();
				pkptr  = op_pk_get(instrm);
				
				elec_pk_arr_actions(pkptr, instrm);
				
				//////////////////////////////////////////////////////////////////////////////
				
				
				}
				FSM_PROFILE_SECTION_OUT (state3_enter_exec)

			/** state (PK_ARRIVAL) exit executives **/
			FSM_STATE_EXIT_FORCED (3, "PK_ARRIVAL", "Oars_Switch [PK_ARRIVAL exit execs]")


			/** state (PK_ARRIVAL) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "PK_ARRIVAL", "idle", "tr_1", "Oars_Switch [PK_ARRIVAL -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (Edg_Eelc_Sw) enter executives **/
			FSM_STATE_ENTER_FORCED (4, "Edg_Eelc_Sw", state4_enter_exec, "Oars_Switch [Edg_Eelc_Sw enter execs]")
				FSM_PROFILE_SECTION_IN ("Oars_Switch [Edg_Eelc_Sw enter execs]", state4_enter_exec)
				{
				//printf("rack_internal_switching\n");
				
				//edg_elec_candidate_list_empty();
				/*dubug*/
				/*
					printf("STATE CHECK : EDG_ELEC_SWITCHING\n ");
					printf("local node address:(%d,%d,%d,%d)\n", local_net_id, local_pod_id, local_switch_id,local_unique_id);
					for(i=0;i<port_num;i++)
						{
						list_len_initial = op_prg_list_size(lptr_elec_candidate_info[i]);
						
						
					    printf("output port: %d\n", i);
					    printf("list len:           %d   \n",list_len_initial);
						
						
						}
					printf("STATE CHECK FINISHED !\n ");
				
				*/
					
				
				
				edg_elec_routing_computation();
				edg_elec_candidate_rolling();
				edg_elec_candidate_list_empty();
				
				//////////////////////////////////////////////////////////////////////////////
				
				
				op_intrpt_schedule_self(op_sim_time()+ packet_data_length/(3*transmission_bandwidth_opc), Edg_Elec_Switching);
				}
				FSM_PROFILE_SECTION_OUT (state4_enter_exec)

			/** state (Edg_Eelc_Sw) exit executives **/
			FSM_STATE_EXIT_FORCED (4, "Edg_Eelc_Sw", "Oars_Switch [Edg_Eelc_Sw exit execs]")


			/** state (Edg_Eelc_Sw) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "Edg_Eelc_Sw", "idle", "tr_4", "Oars_Switch [Edg_Eelc_Sw -> idle : default / ]")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (0,"Oars_Switch")
		}
	}




void
_op_Oars_Switch_diag (OP_SIM_CONTEXT_ARG_OPT)
	{
	/* No Diagnostic Block */
	}




void
_op_Oars_Switch_terminate (OP_SIM_CONTEXT_ARG_OPT)
	{

	FIN_MT (_op_Oars_Switch_terminate ())


	/* No Termination Block */

	Vos_Poolmem_Dealloc (op_sv_ptr);

	FOUT
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in _op_Oars_Switch_svar function. */
#undef port_info
#undef own_objid
#undef node_objid
#undef packet_setup_length
#undef packet_data_length
#undef transmission_bandwidth_ele
#undef packet_ack_length
#undef packet_teardown_length
#undef local_group_id
#undef local_switch_id
#undef local_server_id
#undef transmission_bandwidth_opc
#undef port_num
#undef lptr_elec_candidate_info
#undef lptr_elec_routing_trace_info
#undef stat_conf_handle
#undef stat_conf_count
#undef stat_buf_count
#undef stat_buf_handle

#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE

#define FIN_PREAMBLE_DEC
#define FIN_PREAMBLE_CODE

VosT_Obtype
_op_Oars_Switch_init (int * init_block_ptr)
	{
	VosT_Obtype obtype = OPC_NIL;
	FIN_MT (_op_Oars_Switch_init (init_block_ptr))

	obtype = Vos_Define_Object_Prstate ("proc state vars (Oars_Switch)",
		sizeof (Oars_Switch_state));
	*init_block_ptr = 0;

	FRET (obtype)
	}

VosT_Address
_op_Oars_Switch_alloc (VosT_Obtype obtype, int init_block)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	Oars_Switch_state * ptr;
	FIN_MT (_op_Oars_Switch_alloc (obtype))

	ptr = (Oars_Switch_state *)Vos_Alloc_Object (obtype);
	if (ptr != OPC_NIL)
		{
		ptr->_op_current_block = init_block;
#if defined (OPD_ALLOW_ODB)
		ptr->_op_current_state = "Oars_Switch [inital enter execs]";
#endif
		}
	FRET ((VosT_Address)ptr)
	}



void
_op_Oars_Switch_svar (void * gen_ptr, const char * var_name, void ** var_p_ptr)
	{
	Oars_Switch_state		*prs_ptr;

	FIN_MT (_op_Oars_Switch_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (void *)OPC_NIL;
		FOUT
		}
	prs_ptr = (Oars_Switch_state *)gen_ptr;

	if (strcmp ("port_info" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->port_info);
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
	if (strcmp ("port_num" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->port_num);
		FOUT
		}
	if (strcmp ("lptr_elec_candidate_info" , var_name) == 0)
		{
		*var_p_ptr = (void *) (prs_ptr->lptr_elec_candidate_info);
		FOUT
		}
	if (strcmp ("lptr_elec_routing_trace_info" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->lptr_elec_routing_trace_info);
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
	if (strcmp ("stat_buf_count" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->stat_buf_count);
		FOUT
		}
	if (strcmp ("stat_buf_handle" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->stat_buf_handle);
		FOUT
		}
	*var_p_ptr = (void *)OPC_NIL;

	FOUT
	}

