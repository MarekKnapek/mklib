#include "mk_win_kernel.h"

#include "mk_assert.h"
#include "mk_macros.h"


extern MK_C __declspec(dllimport) void __stdcall DebugBreak(void);
extern MK_C __declspec(dllimport) mk_win_handle_t __stdcall GetCurrentProcess(void);
extern MK_C __declspec(dllimport) mk_win_dword_t __stdcall GetCurrentThreadId(void);
extern MK_C __declspec(dllimport) mk_bool_t __stdcall TerminateProcess(mk_win_handle_t, mk_win_uint_t);
extern MK_C __declspec(dllimport) void __stdcall InitializeCriticalSection(mk_win_kernel_critical_section_t*);
extern MK_C __declspec(dllimport) void __stdcall EnterCriticalSection(mk_win_kernel_critical_section_t*);
extern MK_C __declspec(dllimport) void __stdcall LeaveCriticalSection(mk_win_kernel_critical_section_t*);
extern MK_C __declspec(dllimport) void __stdcall DeleteCriticalSection(mk_win_kernel_critical_section_t*);
extern MK_C __declspec(dllimport) mk_win_handle_t __stdcall GetProcessHeap(void);
extern MK_C __declspec(dllimport) mk_win_handle_t __stdcall HeapCreate(mk_win_dword_t, mk_size_t, mk_size_t);
extern MK_C __declspec(dllimport) void* __stdcall HeapAlloc(mk_win_handle_t, mk_win_dword_t, mk_size_t);
extern MK_C __declspec(dllimport) void* __stdcall HeapReAlloc(mk_win_handle_t, mk_win_dword_t, void*, mk_size_t);
extern MK_C __declspec(dllimport) mk_size_t __stdcall HeapSize(mk_win_handle_t, mk_win_dword_t, void*);
extern MK_C __declspec(dllimport) mk_win_bool_t __stdcall HeapFree(mk_win_handle_t, mk_win_dword_t, void*);
extern MK_C __declspec(dllimport) mk_win_bool_t __stdcall HeapDestroy(mk_win_handle_t);
extern MK_C __declspec(dllimport) mk_win_dword_t __stdcall GetTickCount(void);
extern MK_C __declspec(dllimport) void __stdcall OutputDebugStringA(char const*);
extern MK_C __declspec(dllimport) mk_win_handle_t __stdcall CreateFileW(mk_win_widechar_t const*, mk_win_dword_t, mk_win_dword_t, void*, mk_win_dword_t, mk_win_dword_t, mk_win_handle_t);
extern MK_C __declspec(dllimport) mk_win_bool_t __stdcall CloseHandle(mk_win_handle_t);
extern MK_C __declspec(dllimport) mk_win_dword_t __stdcall GetFileSize(mk_win_handle_t, mk_win_dword_t*);
extern MK_C __declspec(dllimport) mk_win_dword_t __stdcall GetLastError(void);
extern MK_C __declspec(dllimport) mk_win_handle_t __stdcall CreateFileMappingW(mk_win_handle_t, void*, mk_win_dword_t, mk_win_dword_t, mk_win_dword_t, mk_win_widechar_t const*);
extern MK_C __declspec(dllimport) void* __stdcall MapViewOfFile(mk_win_handle_t, mk_win_dword_t, mk_win_dword_t, mk_win_dword_t, mk_size_t);
extern MK_C __declspec(dllimport) mk_win_bool_t __stdcall UnmapViewOfFile(void const*);


void mk_win_kernel_debug_break(void)
{
	DebugBreak();
}

mk_win_handle_t mk_win_kernel_get_current_process(void)
{
	mk_win_handle_t ret;
	ret = GetCurrentProcess();
	return ret;
}

mk_win_dword_t mk_win_kernel_get_current_thread_id(void)
{
	mk_win_dword_t ret;
	ret = GetCurrentThreadId();
	return ret;
}

mk_bool_t mk_win_kernel_terminate_process(mk_win_handle_t const handle, mk_win_uint_t const exit_code)
{
	mk_bool_t ret;
	ret = TerminateProcess(handle, exit_code);
	return ret;
}

void mk_win_kernel_initialize_critical_section(mk_win_kernel_critical_section_t* const critical_section)
{
	InitializeCriticalSection(critical_section);
}

void mk_win_kernel_enter_critical_section(mk_win_kernel_critical_section_t* const critical_section)
{
	EnterCriticalSection(critical_section);
}

void mk_win_kernel_leave_critical_section(mk_win_kernel_critical_section_t* const critical_section)
{
	LeaveCriticalSection(critical_section);
}

void mk_win_kernel_delete_critical_section(mk_win_kernel_critical_section_t* const critical_section)
{
	DeleteCriticalSection(critical_section);
}

mk_win_handle_t mk_win_kernel_get_process_heap(void)
{
	mk_win_handle_t ret;

	ret = GetProcessHeap();
	return ret;
}

mk_win_handle_t mk_win_kernel_heap_create(mk_win_kernel_heap_create_t const options, mk_size_t const initial_size, mk_size_t const maximum_size)
{
	mk_win_dword_t optionss;
	mk_win_handle_t ret;

	optionss.m_value = options;
	ret = HeapCreate(optionss, initial_size, maximum_size);
	return ret;
}

void* mk_win_kernel_heap_alloc(mk_win_handle_t const heap, mk_win_kernel_heap_alloc_t const flags, mk_size_t const bytes)
{
	mk_win_dword_t flagss;
	void* ret;

	flagss.m_value = flags;
	ret = HeapAlloc(heap, flagss, bytes);
	return ret;
}

void* mk_win_kernel_heap_realloc(mk_win_handle_t const heap, mk_win_kernel_heap_realloc_t const flags, void* const mem, mk_size_t const bytes)
{
	void* ret;
	mk_win_dword_t flagss;

	flagss.m_value = flags;
	ret = HeapReAlloc(heap, flagss, mem, bytes);
	return ret;
}

mk_size_t mk_win_kernel_heap_size(mk_win_handle_t const heap, mk_win_kernel_heap_size_t const flags, void* const mem)
{
	mk_win_dword_t flagss;
	mk_size_t ret;

	flagss.m_value = flags;
	ret = HeapSize(heap, flagss, mem);
	return ret;
}

mk_bool_t mk_win_kernel_heap_free(mk_win_handle_t const heap, mk_win_kernel_heap_free_t const flags, void* const mem)
{
	mk_win_dword_t flagss;
	mk_win_bool_t freed;
	mk_bool_t ret;

	flagss.m_value = flags;
	freed = HeapFree(heap, flagss, mem);
	ret = freed.m_value != 0 ? MK_TRUE : MK_FALSE;
	return ret;
}

mk_bool_t mk_win_kernel_heap_destroy(mk_win_handle_t const heap)
{
	mk_win_bool_t destroyed;
	mk_bool_t ret;

	destroyed = HeapDestroy(heap);
	ret = destroyed.m_value != 0 ? MK_TRUE : MK_FALSE;
	return ret;
}

mk_win_dword_t mk_win_kernel_get_tick_count(void)
{
	mk_win_dword_t ret;

	ret = GetTickCount();
	return ret;
}

void mk_win_kernel_output_debug_string(char const* const str)
{
	OutputDebugStringA(str);
}

mk_win_handle_t mk_win_kernel_create_file(mk_win_widechar_t const* const file_name, mk_win_kernel_access_right_generic_t const desired_access, mk_win_kernel_file_share_t const share_mode, void* const security_attributes, mk_win_kernel_file_create_t const creation_disposition, mk_win_kernel_file_attribute_t const flags_and_attributes, mk_win_handle_t const template_file)
{
	mk_win_dword_t desired_access_;
	mk_win_dword_t share_mode_;
	mk_win_dword_t creation_disposition_;
	mk_win_dword_t flags_and_attributes_;
	mk_win_handle_t ret;

	desired_access_.m_value = desired_access;
	share_mode_.m_value = share_mode;
	creation_disposition_.m_value = creation_disposition;
	flags_and_attributes_.m_value = flags_and_attributes;
	ret = CreateFileW(file_name, desired_access_, share_mode_, security_attributes, creation_disposition_, flags_and_attributes_, template_file);
	return ret;
}

mk_bool_t mk_win_kernel_close_handle(mk_win_handle_t const handle)
{
	mk_win_bool_t closed;
	mk_bool_t ret;

	closed = CloseHandle(handle);
	MK_ASSERT(closed.m_value == 0 || closed.m_value == 1);
	ret = closed.m_value != 0 ? MK_TRUE : MK_FALSE;
	return ret;
}

mk_win_dword_t mk_win_kernel_get_file_size(mk_win_handle_t const file, mk_win_dword_t* const size_hi)
{
	mk_win_dword_t ret;

	ret = GetFileSize(file, size_hi);
	return ret;
}

mk_win_dword_t mk_win_kernel_get_last_error(void)
{
	mk_win_dword_t ret;

	ret = GetLastError();
	return ret;
}

mk_win_handle_t mk_win_kernel_create_file_mapping(mk_win_handle_t const file, void* const security_attributes, mk_win_kernel_page_protect_t const page_protect, mk_win_dword_t const max_size_hi, mk_win_dword_t const max_size_lo, mk_win_widechar_t const* const name)
{
	mk_win_dword_t page_protect_;
	mk_win_handle_t ret;

	page_protect_.m_value = page_protect;
	ret = CreateFileMappingW(file, security_attributes, page_protect_, max_size_hi, max_size_lo, name);
	return ret;
}

void* mk_win_kernel_map_view_of_file(mk_win_handle_t const mapping, mk_win_kernel_file_map_t const desired_access, mk_win_dword_t const file_offset_hi, mk_win_dword_t const file_offset_lo, mk_size_t const size)
{
	mk_win_dword_t desired_access_;
	void* ret;

	desired_access_.m_value = desired_access;
	return ret = MapViewOfFile(mapping, desired_access_, file_offset_hi, file_offset_lo, size);
}

mk_bool_t mk_win_kernel_unmap_view_of_file(void const* const ptr)
{
	mk_win_bool_t unmapped;
	mk_bool_t ret;

	unmapped = UnmapViewOfFile(ptr);
	ret = unmapped.m_value != 0 ? MK_TRUE : MK_FALSE;
	return ret;
}
