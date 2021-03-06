// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: enemyroster.proto

#ifndef PROTOBUF_enemyroster_2eproto__INCLUDED
#define PROTOBUF_enemyroster_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

namespace guru {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_enemyroster_2eproto();
void protobuf_AssignDesc_enemyroster_2eproto();
void protobuf_ShutdownFile_enemyroster_2eproto();

class EnemyRoster;

// ===================================================================

class EnemyRoster : public ::google::protobuf::Message {
 public:
  EnemyRoster();
  virtual ~EnemyRoster();
  
  EnemyRoster(const EnemyRoster& from);
  
  inline EnemyRoster& operator=(const EnemyRoster& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const EnemyRoster& default_instance();
  
  void Swap(EnemyRoster* other);
  
  // implements Message ----------------------------------------------
  
  EnemyRoster* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const EnemyRoster& from);
  void MergeFrom(const EnemyRoster& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // repeated uint32 championIds = 1;
  inline int championids_size() const;
  inline void clear_championids();
  static const int kChampionIdsFieldNumber = 1;
  inline ::google::protobuf::uint32 championids(int index) const;
  inline void set_championids(int index, ::google::protobuf::uint32 value);
  inline void add_championids(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      championids() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_championids();
  
  // @@protoc_insertion_point(class_scope:guru.EnemyRoster)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > championids_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_enemyroster_2eproto();
  friend void protobuf_AssignDesc_enemyroster_2eproto();
  friend void protobuf_ShutdownFile_enemyroster_2eproto();
  
  void InitAsDefaultInstance();
  static EnemyRoster* default_instance_;
};
// ===================================================================


// ===================================================================

// EnemyRoster

// repeated uint32 championIds = 1;
inline int EnemyRoster::championids_size() const {
  return championids_.size();
}
inline void EnemyRoster::clear_championids() {
  championids_.Clear();
}
inline ::google::protobuf::uint32 EnemyRoster::championids(int index) const {
  return championids_.Get(index);
}
inline void EnemyRoster::set_championids(int index, ::google::protobuf::uint32 value) {
  championids_.Set(index, value);
}
inline void EnemyRoster::add_championids(::google::protobuf::uint32 value) {
  championids_.Add(value);
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
EnemyRoster::championids() const {
  return championids_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
EnemyRoster::mutable_championids() {
  return &championids_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace guru

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_enemyroster_2eproto__INCLUDED
