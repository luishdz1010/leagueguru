// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "championban.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace guru {

namespace {

const ::google::protobuf::Descriptor* ChampionBan_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ChampionBan_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_championban_2eproto() {
  protobuf_AddDesc_championban_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "championban.proto");
  GOOGLE_CHECK(file != NULL);
  ChampionBan_descriptor_ = file->message_type(0);
  static const int ChampionBan_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ChampionBan, championid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ChampionBan, selfteam_),
  };
  ChampionBan_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ChampionBan_descriptor_,
      ChampionBan::default_instance_,
      ChampionBan_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ChampionBan, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ChampionBan, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ChampionBan));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_championban_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ChampionBan_descriptor_, &ChampionBan::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_championban_2eproto() {
  delete ChampionBan::default_instance_;
  delete ChampionBan_reflection_;
}

void protobuf_AddDesc_championban_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\021championban.proto\022\004guru\"3\n\013ChampionBan"
    "\022\022\n\nchampionId\030\001 \002(\r\022\020\n\010selfTeam\030\002 \002(\010", 78);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "championban.proto", &protobuf_RegisterTypes);
  ChampionBan::default_instance_ = new ChampionBan();
  ChampionBan::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_championban_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_championban_2eproto {
  StaticDescriptorInitializer_championban_2eproto() {
    protobuf_AddDesc_championban_2eproto();
  }
} static_descriptor_initializer_championban_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int ChampionBan::kChampionIdFieldNumber;
const int ChampionBan::kSelfTeamFieldNumber;
#endif  // !_MSC_VER

ChampionBan::ChampionBan()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void ChampionBan::InitAsDefaultInstance() {
}

ChampionBan::ChampionBan(const ChampionBan& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void ChampionBan::SharedCtor() {
  _cached_size_ = 0;
  championid_ = 0u;
  selfteam_ = false;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ChampionBan::~ChampionBan() {
  SharedDtor();
}

void ChampionBan::SharedDtor() {
  if (this != default_instance_) {
  }
}

void ChampionBan::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ChampionBan::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ChampionBan_descriptor_;
}

const ChampionBan& ChampionBan::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_championban_2eproto();  return *default_instance_;
}

ChampionBan* ChampionBan::default_instance_ = NULL;

ChampionBan* ChampionBan::New() const {
  return new ChampionBan;
}

void ChampionBan::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    championid_ = 0u;
    selfteam_ = false;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ChampionBan::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 championId = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &championid_)));
          set_has_championid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_selfTeam;
        break;
      }
      
      // required bool selfTeam = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_selfTeam:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &selfteam_)));
          set_has_selfteam();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void ChampionBan::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 championId = 1;
  if (has_championid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->championid(), output);
  }
  
  // required bool selfTeam = 2;
  if (has_selfteam()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(2, this->selfteam(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* ChampionBan::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 championId = 1;
  if (has_championid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->championid(), target);
  }
  
  // required bool selfTeam = 2;
  if (has_selfteam()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(2, this->selfteam(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int ChampionBan::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 championId = 1;
    if (has_championid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->championid());
    }
    
    // required bool selfTeam = 2;
    if (has_selfteam()) {
      total_size += 1 + 1;
    }
    
  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ChampionBan::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ChampionBan* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ChampionBan*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ChampionBan::MergeFrom(const ChampionBan& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_championid()) {
      set_championid(from.championid());
    }
    if (from.has_selfteam()) {
      set_selfteam(from.selfteam());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ChampionBan::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ChampionBan::CopyFrom(const ChampionBan& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ChampionBan::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  
  return true;
}

void ChampionBan::Swap(ChampionBan* other) {
  if (other != this) {
    std::swap(championid_, other->championid_);
    std::swap(selfteam_, other->selfteam_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ChampionBan::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ChampionBan_descriptor_;
  metadata.reflection = ChampionBan_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace guru

// @@protoc_insertion_point(global_scope)
