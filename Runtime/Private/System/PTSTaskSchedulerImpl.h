//Robert D. Blumofe, Charles E. Leiserson. "Scheduling Multithreaded Computations by Work Stealing." Journal of the ACM 1999. //�̵߳ĸ����ڵ�ʱ��δ�ռ� �����е�"Thread"�ڵ���ָ"Task" �����е�"Processor"�ڵ���ָ"Thread"
//Jeffrey Richter. ".NET Column: The CLR's Thread Pool." MSDN Magazine June 2003.(https://msdn.microsoft.com/en-us/magazine/msdn-magazine-issues.aspx)
//Alexey Kukanov, Michael J.Voss. "The Foundations for Scalable Multi-core Software in Intel Threading Building Blocks." Intel Technology Journal, Volume11, Issue 4 2007.

//Andrey Marochko. "Exception Handling and Cancellation in TBB - Part II �C Basic use cases." Intel Developer Zone 2008. (https://software.intel.com/en-us/blogs/2008/05/29/exception-handling-and-cancellation-in-tbb-part-ii-basic-use-cases)
//Andrey Marochko. "Exception Handling and Cancellation in TBB - Part III �C Use cases with nested parallelism." Intel Developer Zone 2008. (https://software.intel.com/en-us/blogs/2008/06/04/exception-handling-and-cancellation-in-tbb-part-iii-use-cases-with-nested-parallelism)
//Andrey Marochko. "Exception Handling and Cancellation in TBB - Part IV �C Using context objects." Intel Developer Zone 2008. (https://software.intel.com/en-us/blogs/2008/06/11/exception-handling-and-cancellation-in-tbb-part-iv-using-context-objects)
//Andrey Marochko. "Exception handling in TBB 2.2 - Getting ready for C++0x." Intel Developer Zone 2009.��https://software.intel.com/en-us/blogs/2009/08/18/exception-handling-in-tbb-22-getting-ready-for-c0x��

//Andrey Marochko. "TBB 3.0 task scheduler improves composability of TBB based solutions. Part 1." Intel Developer Zone 2010. (https://software.intel.com/en-us/blogs/2010/05/13/tbb-30-task-scheduler-improves-composability-of-tbb-based-solutions-part-1)
//Andrey Marochko. "TBB 3.0 task scheduler improves composability of TBB based solutions. Part 2." Intel Developer Zone 2010. (https://software.intel.com/en-us/blogs/2010/05/21/tbb-30-task-scheduler-improves-composability-of-tbb-based-solutions-part-2)
//Andrey Marochko. "TBB scheduler clandestine evolution." Intel Developer Zone 2010. (https://software.intel.com/en-us/blogs/2010/12/09/tbb-scheduler-clandestine-evolution)
//Andrey Marochko. "TBB 3.0, high end many - cores, and Windows processor groups." Intel Developer Zone 2010. (https://software.intel.com/en-us/blogs/2010/12/09/tbb-scheduler-clandestine-evolution)
//Andrey Marochko. "TBB 3.0 and processor affinity." Intel Developer Zone 2010. (https://software.intel.com/en-us/blogs/2010/12/28/tbb-30-and-processor-affinity)
//Andrey Marochko. "Task and task group priorities in TBB." Intel Developer Zone 2011. (https://software.intel.com/en-us/blogs/2011/04/01/task-and-task-group-priorities-in-tbb)

//Andrey Marochko. "TBB initialization, termination, and resource management details, juicy and gory." Intel Developer Zone 2011. (https://software.intel.com/en-us/blogs/2011/04/09/tbb-initialization-termination-and-resource-management-details-juicy-and-gory)


#include "../../Public/System/PTSTaskScheduler.h"
#include <stdlib.h>

#if defined(PTARM) || defined(PTARM64) || defined(PTX86) || defined(PTX64)
static uint32_t const s_CacheLine_Size = 64U;
#else
#error δ֪�ļܹ�
#endif

class PTSArena;

//TaskScheduler
//��ۣ�Facade��ģʽ
//Associated with this Master Thread is created.
//Any thread executing TBB tasks (whether Master or Worker) has its own instance of this component, which is stored in a TLS slot.
class PTSTaskSchedulerMasterImpl : public IPTSTaskScheduler
{
	PTSArena *m_pArena;
	uint32_t m_Slot_Index;

public:
	//TBB������Ӧ�ó�����ʾ���Ʋ���
	//Worker_Wake: arena::advertise_new_work->market::adjust_demand->private_server/rml_server::adjust_job_count_estimate
	//Worker_Sleep: arena::is_out_of_work->market::adjust_demand->private_server/rml_server::adjust_job_count_estimate
	void Worker_Wake() override;
	void Worker_Sleep() override;

private:
	IPTSTask *Task_Allocate(size_t Size, size_t Alignment) override;

	void Task_Spawn(IPTSTask *pTask) override;
	void Task_Spawn_Root_And_Wait(IPTSTask *pTask) override;

public:
	inline PTSTaskSchedulerMasterImpl(PTSArena *pArena, uint32_t Slot_Index);
};

//Resource Management Layer
//RML�ϲ���Market

//�г�
//Market
//Singleton is instantiated.
//This component is responsible for assigning Worker Threads to different Arenas.
class PTSMarket
{
	PTSArena **m_ArenaPointerArrayMemory; //64
	
	uint32_t m_ArenaPointerArraySize; //ֻ��Push ����Push ������ABA //��SizeΪ0ʱ ���� �ɻ���

	uint8_t __PaddingForPublicFields[s_CacheLine_Size - sizeof(uint32_t) - sizeof(void *)];

	PTSThread *m_ThreadArrayMemory;

	PTSSemaphore m_Semaphore;

	uint32_t const m_ThreadNumber;

	uint32_t const m_ArenaPointerArrayCapacity; //64

	uint8_t __PaddingForPrivateFields[s_CacheLine_Size - sizeof(uint32_t) * 2U - sizeof(PTSSemaphore) - sizeof(void *)];
public:
	inline PTSMarket(uint32_t ThreadNumber);
	
	inline PTSArena *Arena_Allocate(float fThreadNumberRatio);

	inline PTSArena *Arena_Acquire(uint32_t *pSlot_Index);

	inline void Worker_Wake(uint32_t ThreadNumber);

	inline void Worker_Sleep(uint32_t ThreadNumber);

#ifdef PTWIN32
	static inline unsigned __stdcall Worker_Thread_Main(void *pMarketVoid);
#elif defined(PTPOSIX)
	static inline void * Worker_Thread_Main(void *pMarketVoid);
#else
#error δ֪��ƽ̨
#endif

	static inline bool constexpr StaticAssert()
	{
		return (offsetof(PTSMarket, m_ThreadArrayMemory) == s_CacheLine_Size) && (sizeof(PTSMarket) == s_CacheLine_Size * 2U);
	}
};
static_assert(PTSMarket::StaticAssert(), "PTSMarket: Padding Not Correct");

class PTSArenaSlot;

//��̨
//Arena
//Associated with this Master Thread is allocated.
//Just created local task dispatcher registers itself in its arena, 
//arena is added into market��s list that tracks all existing arenas, 
//and market refcount is incremented.
class PTSArena
{
	uint32_t m_SlotIndexMaximum;

	uint32_t m_SlotArraySize;

	//����α����
	uint8_t __PaddingForPublicFields[s_CacheLine_Size - sizeof(uint32_t) * 2U];

	PTSArenaSlot * const m_SlotArrayMemory;
	
	uint32_t const m_SlotArrayCapacity;

	//���뵽CacheLine
	uint8_t __PaddingForPrivateFields[s_CacheLine_Size - sizeof(uint32_t) - sizeof(void*)];

	friend void PTSTaskSchedulerMasterImpl::Worker_Wake();
	friend void PTSTaskSchedulerMasterImpl::Worker_Sleep();

public:
	inline PTSArena(uint32_t Capacity);

	//MasterThread��SlotIndexһ��Ϊ0
	inline bool Slot_Acquire_Master();

	inline PTSArenaSlot *Slot_Acquire(uint32_t *pSlot_Index);

	inline void Slot_Release(uint32_t Slot_Index);

	inline uint32_t SlotIndexMaximum_Load_Acquire();

	inline uint32_t Size_Load_Acquire();

	inline PTSArenaSlot *Slot(uint32_t Index);

	inline uint32_t Capacity();

	static inline bool constexpr StaticAssert()
	{
		return (offsetof(PTSArena, m_SlotArrayMemory) == s_CacheLine_Size) && (sizeof(PTSArena) == s_CacheLine_Size * 2U);
	}
};
static_assert(PTSArena::StaticAssert(), "PTSArena: Padding Not Correct");

class PTSTaskPrefixImpl;

//Arena Slot����̨�ۣ�
//The Deque
//The first one is the number of Arena Slots that define maximal number of Workers 
//available for parallel algorithms started by this Master (or, in other words, their maximal concurrency level).
class PTSArenaSlot
{
	union
	{
		struct
		{
			uint32_t m_Head;
			uint32_t m_Tail;
		}m_OneWord;
		uint64_t m_TwoWord;
	}m_HeadAndTail;

	uint32_t m_HasBeenAcquired;

	//Ϊ����α�����������ܱ�Thief�̷߳��ʵ�Public���ֻ�ܱ�Owner�̷߳��ʵ�Private��ָ��ڲ�ͬ�Ļ�������
	uint8_t __PaddingForPublicFields[s_CacheLine_Size - sizeof(uint32_t) - sizeof(int64_t)];

	PTSTaskPrefixImpl * * m_TaskDequeMemoryS[4]; //64(1)+64(1)+128(2)

	uint32_t m_TaskDequeCapacity;

	//�ָ�Metadata���û�����
	uint8_t __PaddingForPrivateFields[s_CacheLine_Size - sizeof(uint32_t) - sizeof(void*) * 4U];

	friend PTSArena::PTSArena(uint32_t Capacity);
	friend PTSArena *PTSMarket::Arena_Allocate(float fThreadNumberRatio);
	friend bool PTSArena::Slot_Acquire_Master();
	friend PTSArenaSlot * PTSArena::Slot_Acquire(uint32_t *pSlot_Index);
	friend void PTSArena::Slot_Release(uint32_t Slot_Index);
public:
	inline PTSArenaSlot();

	inline void TaskDeque_Push(PTSTaskPrefixImpl *pTaskToPush);

	inline PTSTaskPrefixImpl * TaskDeque_Pop_Private();

	inline PTSTaskPrefixImpl * TaskDeque_Pop_Public();

	static inline bool constexpr StaticAssert()
	{
		return (offsetof(PTSArenaSlot, m_TaskDequeMemoryS[0]) == s_CacheLine_Size) && (sizeof(PTSArenaSlot) == s_CacheLine_Size * 2U);
	}
};
static_assert(PTSArenaSlot::StaticAssert(), "PTSArenaSlot: Padding Not Correct");


//
class PTSTaskPrefixImpl :public IPTSTaskPrefix
{
	IPTSTaskPrefix * Parent() override;

	void ParentSet(IPTSTaskPrefix *pParent) override;

	void Recycle_AsChildOf(IPTSTaskPrefix *pParent) override;

	void RefCount_Set(uint32_t RefCount) override;

	void OverrideExecute(IPTSTask *(*pFn_Execute)(IPTSTask *pTaskThisVoid))  override;

public:
	PTSTaskPrefixImpl * m_Parent;

	uint32_t m_RefCount; //Count Of Child

	IPTSTask *(*m_pFn_Execute)(IPTSTask *pTaskThis);

	enum :uint8_t
	{
		Allocated = 0U,
		Ready = 1U,
		Executing = 2U,
		Freed = 4U,
		Debug_RefCount_InUse = 8U
	};

	uint8_t m_State;

	inline PTSTaskPrefixImpl();

	inline PTSTaskPrefixImpl *Execute();
};

static uint32_t const s_TaskPrefix_Alignment = 32U;
static inline PTSTaskPrefixImpl * PTS_Internal_Task_Prefix(IPTSTask *pTask);

class PTSTaskSchedulerWorkerImpl : public IPTSTaskScheduler
{
	PTSArena *m_pArena;
	uint32_t m_Slot_Index;

	void Worker_Wake() override;
	void Worker_Sleep() override;

	IPTSTask *Task_Allocate(size_t Size, size_t Alignment) override;

	void Task_Spawn(IPTSTask *pTask) override;
	void Task_Spawn_Root_And_Wait(IPTSTask *pTask) override;

	friend unsigned __stdcall PTSMarket::Worker_Thread_Main(void *pMarketVoid);

public:
	inline PTSTaskSchedulerWorkerImpl();
};