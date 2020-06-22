#pragma once

#pragma region CDTOR

#define MAKE_CDTOR_COPY_MOVE_EMPTY(CLASS)\
public:\
CLASS() noexcept;\
virtual ~CLASS() noexcept;\
CLASS(const CLASS&) noexcept;\
CLASS(CLASS&&) noexcept;\
CLASS& operator=(const CLASS&) noexcept;\
CLASS& operator=(CLASS&&) noexcept;

#define MAKE_CDTOR_COPY_MOVE_EMPTY_TEMPLATE(CLASS, TYPE)\
public:\
CLASS() noexcept;\
virtual ~CLASS() noexcept;\
CLASS(const CLASS<TYPE>&) noexcept;\
CLASS(CLASS<TYPE>&&) noexcept;\
CLASS<TYPE>& operator=(const CLASS<TYPE>&) noexcept;\
CLASS<TYPE>& operator=(CLASS<TYPE>&&) noexcept;

#define MAKE_CDTOR_DEFAULT_COPY_MOVE(CLASS)\
public:\
CLASS() noexcept;\
virtual ~CLASS() noexcept;\
CLASS(const CLASS&) noexcept;\
CLASS(CLASS&&) noexcept;\
CLASS& operator=(const CLASS&) = default;\
CLASS& operator=(CLASS&&) = default;

#define MAKE_CDTOR_DEFAULT_COPY_MOVE_TEMPLATE(CLASS, TYPE)\
public:\
CLASS() noexcept;\
virtual ~CLASS() noexcept;\
CLASS(const CLASS<TYPE>&) noexcept;\
CLASS(CLASS<TYPE>&&) noexcept;\
CLASS<TYPE>& operator=(const CLASS<TYPE>&) = default;\
CLASS<TYPE>& operator=(CLASS<TYPE>&&) = default;

#define MAKE_CDTOR_COPY_DEFAULT_MOVE(CLASS)\
public:\
CLASS() noexcept;\
virtual ~CLASS() noexcept;\
CLASS(const CLASS&) = default;\
CLASS(CLASS&&) = default;\
CLASS& operator=(const CLASS&) = default;\
CLASS& operator=(CLASS&&) = default;

#define MAKE_CDTOR_COPY_DEFAULT_MOVE_TEMPLATE(CLASS, TYPE)\
public:\
CLASS() noexcept;\
virtual ~CLASS() noexcept;\
CLASS(const CLASS<TYPE>&) = default;\
CLASS(CLASS<TYPE>&&) = default;\
CLASS<TYPE>& operator=(const CLASS<TYPE>&) = default;\
CLASS<TYPE>& operator=(CLASS<TYPE>&&) = default;

#define MAKE_CDTOR_COPY_MOVE_DEFAULT(CLASS)\
public:\
CLASS() = default;\
virtual ~CLASS() = default;\
CLASS(const CLASS&) = default;\
CLASS(CLASS&&) = default;\
CLASS& operator=(const CLASS&) = default;\
CLASS& operator=(CLASS&&) = default;

#define MAKE_CDTOR_COPY_MOVE_DEFAULT_TEMPLATE(CLASS, TYPE)\
public:\
CLASS() = default;\
virtual ~CLASS() = default;\
CLASS(const CLASS<TYPE>&) = default;\
CLASS(CLASS<TYPE>&&) = default;\
CLASS<TYPE>& operator=(const CLASS<TYPE>&) = default;\
CLASS<TYPE>& operator=(CLASS<TYPE>&&) = default;

#define MAKE_CDTOR_DEFAULT(CLASS)\
public:\
CLASS() = default;\
virtual ~CLASS() = default;

#define MAKE_CDTOR_DEFAULT_TEMPLATE(CLASS, TYPE) MAKE_CDTOR_DEFAULT(CLASS)

#define MAKE_COPY_DEFAULT(CLASS)\
public:\
CLASS(const CLASS&) = default;\
CLASS& operator=(const CLASS&) = default;

#define MAKE_COPY_DEFAULT_TEMPLATE(CLASS, TYPE)\
public:\
CLASS(const CLASS<TYPE>&) = default;\
CLASS<TYPE>& operator=(const CLASS<TYPE>&) = default;

#define MAKE_MOVE_DEFAULT(CLASS)\
public:\
CLASS(CLASS&&) = default;\
CLASS& operator=(CLASS&&) = default;

#define MAKE_MOVE_DEFAULT_TEMPLATE(CLASS, TYPE)\
public:\
CLASS(CLASS<TYPE>&&) = default;\
CLASS<TYPE>& operator=(CLASS<TYPE>&&) = default;

#define DELETE_CDTOR_COPY_MOVE(CLASS)\
public:\
CLASS() = delete;\
virtual ~CLASS() = delete;\
CLASS(const CLASS&) = delete;\
CLASS(CLASS&&) = delete;\
CLASS& operator=(const CLASS&) = delete;\
CLASS& operator=(CLASS&&) = delete;

#define DELETE_CDTOR_COPY_MOVE_TEMPLATE(CLASS, TYPE)\
public:\
CLASS() = delete;\
~CLASS() = delete;\
CLASS(const CLASS<TYPE>&) = delete;\
CLASS<TYPE>& operator=(const CLASS<TYPE>&) = delete;\
CLASS(CLASS<TYPE>&&) = delete;\
CLASS<TYPE>& operator=(CLASS<TYPE>&&) = delete;

#define DELETE_CDTOR(CLASS)\
public:\
CLASS() = delete;\
virtual ~CLASS() = delete;

#define DELETE_CDTOR_TEMPLATE(CLASS, TYPE) DELETE_CDTOR(CLASS)

#define DELETE_COPY(CLASS)\
public:\
CLASS(const CLASS&) = delete;\
CLASS& operator=(const CLASS&) = delete;

#define DELETE_COPY_TEMPLATE(CLASS, TYPE)\
public:\
CLASS(const CLASS<TYPE>&) = delete;\
CLASS<TYPE>& operator=(const CLASS<TYPE>&) = delete;

#define DELETE_MOVE(CLASS)\
public:\
CLASS(CLASS&&) = delete;\
CLASS& operator=(CLASS&&) = delete;

#define DELETE_MOVE_TEMPLATE(CLASS, TYPE)\
public:\
CLASS(CLASS<TYPE>&&) = delete;\
CLASS<TYPE>& operator=(CLASS<TYPE>&&) = delete;

#define DELETE_COPY_MOVE(CLASS) DELETE_COPY(CLASS); DELETE_MOVE(CLASS)
#define DELETE_COPY_MOVE_TEMPLATE(CLASS, TYPE) DELETE_COPY_TEMPLATE(CLASS, TYPE); DELETE_MOVE_TEMPLATE(CLASS, TYPE)

#pragma endregion

#pragma region BEHAVIOUR

#define SDELA(Arr)\
do { delete[]Arr; Arr=nullptr; } while (Arr!=nullptr)

#define SDELA2(Arr)\
while (Arr!=nullptr) {delete[]Arr; Arr=nullptr; }

#define SDEL(Ptr)\
do {delete Ptr; Ptr = nullptr; } while (Ptr!=nullptr)

#define SDEL2(Ptr)\
while (Ptr!=nullptr) {delete Ptr; Ptr=nullptr; }

#pragma endregion
