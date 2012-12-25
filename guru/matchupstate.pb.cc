// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "matchupstate.pb.h"

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

const ::google::protobuf::Descriptor* MatchupState_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  MatchupState_reflection_ = NULL;
const ::google::protobuf::Descriptor* MatchupState_ParticipantState_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  MatchupState_ParticipantState_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_matchupstate_2eproto() {
  protobuf_AddDesc_matchupstate_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "matchupstate.proto");
  GOOGLE_CHECK(file != NULL);
  MatchupState_descriptor_ = file->message_type(0);
  static const int MatchupState_offsets_[6] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MatchupState, matchupinfo_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MatchupState, enemyroster_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MatchupState, championbans_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MatchupState, participantstate_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MatchupState, bansuggestions_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MatchupState, participantssugestions_),
  };
  MatchupState_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      MatchupState_descriptor_,
      MatchupState::default_instance_,
      MatchupState_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MatchupState, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MatchupState, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(MatchupState));
  MatchupState_ParticipantState_descriptor_ = MatchupState_descriptor_->nested_type(0);
  static const int MatchupState_ParticipantState_offsets_[8] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MatchupState_ParticipantState, participant_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MatchupState_ParticipantState, pickingstart_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MatchupState_ParticipantState, pickingtimer_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MatchupState_ParticipantState, spell1_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MatchupState_ParticipantState, spell2_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MatchupState_ParticipantState, championid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MatchupState_ParticipantState, role_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MatchupState_ParticipantState, locked_),
  };
  MatchupState_ParticipantState_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      MatchupState_ParticipantState_descriptor_,
      MatchupState_ParticipantState::default_instance_,
      MatchupState_ParticipantState_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MatchupState_ParticipantState, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MatchupState_ParticipantState, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(MatchupState_ParticipantState));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_matchupstate_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    MatchupState_descriptor_, &MatchupState::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    MatchupState_ParticipantState_descriptor_, &MatchupState_ParticipantState::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_matchupstate_2eproto() {
  delete MatchupState::default_instance_;
  delete MatchupState_reflection_;
  delete MatchupState_ParticipantState::default_instance_;
  delete MatchupState_ParticipantState_reflection_;
}

void protobuf_AddDesc_matchupstate_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::guru::protobuf_AddDesc_matchupinfo_2eproto();
  ::guru::protobuf_AddDesc_enemyroster_2eproto();
  ::guru::protobuf_AddDesc_championban_2eproto();
  ::guru::protobuf_AddDesc_bansuggestions_2eproto();
  ::guru::protobuf_AddDesc_participantssuggestions_2eproto();
  ::guru::protobuf_AddDesc_participantrole_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\022matchupstate.proto\022\004guru\032\021matchupinfo."
    "proto\032\021enemyroster.proto\032\021championban.pr"
    "oto\032\024bansuggestions.proto\032\035participantss"
    "uggestions.proto\032\025participantrole.proto\""
    "\357\003\n\014MatchupState\022&\n\013matchupInfo\030\001 \002(\0132\021."
    "guru.MatchupInfo\022&\n\013enemyRoster\030\002 \001(\0132\021."
    "guru.EnemyRoster\022\'\n\014championBans\030\003 \003(\0132\021"
    ".guru.ChampionBan\022=\n\020participantState\030\004 "
    "\003(\0132#.guru.MatchupState.ParticipantState"
    "\022,\n\016banSuggestions\030\005 \001(\0132\024.guru.BanSugge"
    "stions\022=\n\026participantsSugestions\030\006 \001(\0132\035"
    ".guru.ParticipantsSuggestions\032\271\001\n\020Partic"
    "ipantState\022\023\n\013participant\030\001 \002(\r\022\024\n\014picki"
    "ngStart\030\002 \001(\006\022\024\n\014pickingTimer\030\003 \001(\r\022\016\n\006s"
    "pell1\030\004 \001(\r\022\016\n\006spell2\030\005 \001(\r\022\022\n\nchampionI"
    "d\030\006 \001(\r\022 \n\004role\030\007 \001(\0162\022.guru.ChampionRol"
    "e\022\016\n\006locked\030\010 \001(\010", 657);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "matchupstate.proto", &protobuf_RegisterTypes);
  MatchupState::default_instance_ = new MatchupState();
  MatchupState_ParticipantState::default_instance_ = new MatchupState_ParticipantState();
  MatchupState::default_instance_->InitAsDefaultInstance();
  MatchupState_ParticipantState::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_matchupstate_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_matchupstate_2eproto {
  StaticDescriptorInitializer_matchupstate_2eproto() {
    protobuf_AddDesc_matchupstate_2eproto();
  }
} static_descriptor_initializer_matchupstate_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int MatchupState_ParticipantState::kParticipantFieldNumber;
const int MatchupState_ParticipantState::kPickingStartFieldNumber;
const int MatchupState_ParticipantState::kPickingTimerFieldNumber;
const int MatchupState_ParticipantState::kSpell1FieldNumber;
const int MatchupState_ParticipantState::kSpell2FieldNumber;
const int MatchupState_ParticipantState::kChampionIdFieldNumber;
const int MatchupState_ParticipantState::kRoleFieldNumber;
const int MatchupState_ParticipantState::kLockedFieldNumber;
#endif  // !_MSC_VER

MatchupState_ParticipantState::MatchupState_ParticipantState()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void MatchupState_ParticipantState::InitAsDefaultInstance() {
}

MatchupState_ParticipantState::MatchupState_ParticipantState(const MatchupState_ParticipantState& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void MatchupState_ParticipantState::SharedCtor() {
  _cached_size_ = 0;
  participant_ = 0u;
  pickingstart_ = GOOGLE_ULONGLONG(0);
  pickingtimer_ = 0u;
  spell1_ = 0u;
  spell2_ = 0u;
  championid_ = 0u;
  role_ = 0;
  locked_ = false;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

MatchupState_ParticipantState::~MatchupState_ParticipantState() {
  SharedDtor();
}

void MatchupState_ParticipantState::SharedDtor() {
  if (this != default_instance_) {
  }
}

void MatchupState_ParticipantState::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* MatchupState_ParticipantState::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MatchupState_ParticipantState_descriptor_;
}

const MatchupState_ParticipantState& MatchupState_ParticipantState::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_matchupstate_2eproto();  return *default_instance_;
}

MatchupState_ParticipantState* MatchupState_ParticipantState::default_instance_ = NULL;

MatchupState_ParticipantState* MatchupState_ParticipantState::New() const {
  return new MatchupState_ParticipantState;
}

void MatchupState_ParticipantState::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    participant_ = 0u;
    pickingstart_ = GOOGLE_ULONGLONG(0);
    pickingtimer_ = 0u;
    spell1_ = 0u;
    spell2_ = 0u;
    championid_ = 0u;
    role_ = 0;
    locked_ = false;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool MatchupState_ParticipantState::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 participant = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &participant_)));
          set_has_participant();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(17)) goto parse_pickingStart;
        break;
      }
      
      // optional fixed64 pickingStart = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_pickingStart:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_FIXED64>(
                 input, &pickingstart_)));
          set_has_pickingstart();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_pickingTimer;
        break;
      }
      
      // optional uint32 pickingTimer = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_pickingTimer:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &pickingtimer_)));
          set_has_pickingtimer();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_spell1;
        break;
      }
      
      // optional uint32 spell1 = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_spell1:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &spell1_)));
          set_has_spell1();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_spell2;
        break;
      }
      
      // optional uint32 spell2 = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_spell2:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &spell2_)));
          set_has_spell2();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(48)) goto parse_championId;
        break;
      }
      
      // optional uint32 championId = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_championId:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &championid_)));
          set_has_championid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(56)) goto parse_role;
        break;
      }
      
      // optional .guru.ChampionRole role = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_role:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (guru::ChampionRole_IsValid(value)) {
            set_role(static_cast< guru::ChampionRole >(value));
          } else {
            mutable_unknown_fields()->AddVarint(7, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(64)) goto parse_locked;
        break;
      }
      
      // optional bool locked = 8;
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_locked:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &locked_)));
          set_has_locked();
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

void MatchupState_ParticipantState::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 participant = 1;
  if (has_participant()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->participant(), output);
  }
  
  // optional fixed64 pickingStart = 2;
  if (has_pickingstart()) {
    ::google::protobuf::internal::WireFormatLite::WriteFixed64(2, this->pickingstart(), output);
  }
  
  // optional uint32 pickingTimer = 3;
  if (has_pickingtimer()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->pickingtimer(), output);
  }
  
  // optional uint32 spell1 = 4;
  if (has_spell1()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->spell1(), output);
  }
  
  // optional uint32 spell2 = 5;
  if (has_spell2()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(5, this->spell2(), output);
  }
  
  // optional uint32 championId = 6;
  if (has_championid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(6, this->championid(), output);
  }
  
  // optional .guru.ChampionRole role = 7;
  if (has_role()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      7, this->role(), output);
  }
  
  // optional bool locked = 8;
  if (has_locked()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(8, this->locked(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* MatchupState_ParticipantState::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 participant = 1;
  if (has_participant()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->participant(), target);
  }
  
  // optional fixed64 pickingStart = 2;
  if (has_pickingstart()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFixed64ToArray(2, this->pickingstart(), target);
  }
  
  // optional uint32 pickingTimer = 3;
  if (has_pickingtimer()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->pickingtimer(), target);
  }
  
  // optional uint32 spell1 = 4;
  if (has_spell1()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->spell1(), target);
  }
  
  // optional uint32 spell2 = 5;
  if (has_spell2()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(5, this->spell2(), target);
  }
  
  // optional uint32 championId = 6;
  if (has_championid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(6, this->championid(), target);
  }
  
  // optional .guru.ChampionRole role = 7;
  if (has_role()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      7, this->role(), target);
  }
  
  // optional bool locked = 8;
  if (has_locked()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(8, this->locked(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int MatchupState_ParticipantState::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 participant = 1;
    if (has_participant()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->participant());
    }
    
    // optional fixed64 pickingStart = 2;
    if (has_pickingstart()) {
      total_size += 1 + 8;
    }
    
    // optional uint32 pickingTimer = 3;
    if (has_pickingtimer()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->pickingtimer());
    }
    
    // optional uint32 spell1 = 4;
    if (has_spell1()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->spell1());
    }
    
    // optional uint32 spell2 = 5;
    if (has_spell2()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->spell2());
    }
    
    // optional uint32 championId = 6;
    if (has_championid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->championid());
    }
    
    // optional .guru.ChampionRole role = 7;
    if (has_role()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->role());
    }
    
    // optional bool locked = 8;
    if (has_locked()) {
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

void MatchupState_ParticipantState::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const MatchupState_ParticipantState* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const MatchupState_ParticipantState*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void MatchupState_ParticipantState::MergeFrom(const MatchupState_ParticipantState& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_participant()) {
      set_participant(from.participant());
    }
    if (from.has_pickingstart()) {
      set_pickingstart(from.pickingstart());
    }
    if (from.has_pickingtimer()) {
      set_pickingtimer(from.pickingtimer());
    }
    if (from.has_spell1()) {
      set_spell1(from.spell1());
    }
    if (from.has_spell2()) {
      set_spell2(from.spell2());
    }
    if (from.has_championid()) {
      set_championid(from.championid());
    }
    if (from.has_role()) {
      set_role(from.role());
    }
    if (from.has_locked()) {
      set_locked(from.locked());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void MatchupState_ParticipantState::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MatchupState_ParticipantState::CopyFrom(const MatchupState_ParticipantState& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MatchupState_ParticipantState::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;
  
  return true;
}

void MatchupState_ParticipantState::Swap(MatchupState_ParticipantState* other) {
  if (other != this) {
    std::swap(participant_, other->participant_);
    std::swap(pickingstart_, other->pickingstart_);
    std::swap(pickingtimer_, other->pickingtimer_);
    std::swap(spell1_, other->spell1_);
    std::swap(spell2_, other->spell2_);
    std::swap(championid_, other->championid_);
    std::swap(role_, other->role_);
    std::swap(locked_, other->locked_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata MatchupState_ParticipantState::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = MatchupState_ParticipantState_descriptor_;
  metadata.reflection = MatchupState_ParticipantState_reflection_;
  return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int MatchupState::kMatchupInfoFieldNumber;
const int MatchupState::kEnemyRosterFieldNumber;
const int MatchupState::kChampionBansFieldNumber;
const int MatchupState::kParticipantStateFieldNumber;
const int MatchupState::kBanSuggestionsFieldNumber;
const int MatchupState::kParticipantsSugestionsFieldNumber;
#endif  // !_MSC_VER

MatchupState::MatchupState()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void MatchupState::InitAsDefaultInstance() {
  matchupinfo_ = const_cast< ::guru::MatchupInfo*>(&::guru::MatchupInfo::default_instance());
  enemyroster_ = const_cast< ::guru::EnemyRoster*>(&::guru::EnemyRoster::default_instance());
  bansuggestions_ = const_cast< ::guru::BanSuggestions*>(&::guru::BanSuggestions::default_instance());
  participantssugestions_ = const_cast< ::guru::ParticipantsSuggestions*>(&::guru::ParticipantsSuggestions::default_instance());
}

MatchupState::MatchupState(const MatchupState& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void MatchupState::SharedCtor() {
  _cached_size_ = 0;
  matchupinfo_ = NULL;
  enemyroster_ = NULL;
  bansuggestions_ = NULL;
  participantssugestions_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

MatchupState::~MatchupState() {
  SharedDtor();
}

void MatchupState::SharedDtor() {
  if (this != default_instance_) {
    delete matchupinfo_;
    delete enemyroster_;
    delete bansuggestions_;
    delete participantssugestions_;
  }
}

void MatchupState::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* MatchupState::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MatchupState_descriptor_;
}

const MatchupState& MatchupState::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_matchupstate_2eproto();  return *default_instance_;
}

MatchupState* MatchupState::default_instance_ = NULL;

MatchupState* MatchupState::New() const {
  return new MatchupState;
}

void MatchupState::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_matchupinfo()) {
      if (matchupinfo_ != NULL) matchupinfo_->::guru::MatchupInfo::Clear();
    }
    if (has_enemyroster()) {
      if (enemyroster_ != NULL) enemyroster_->::guru::EnemyRoster::Clear();
    }
    if (has_bansuggestions()) {
      if (bansuggestions_ != NULL) bansuggestions_->::guru::BanSuggestions::Clear();
    }
    if (has_participantssugestions()) {
      if (participantssugestions_ != NULL) participantssugestions_->::guru::ParticipantsSuggestions::Clear();
    }
  }
  championbans_.Clear();
  participantstate_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool MatchupState::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .guru.MatchupInfo matchupInfo = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_matchupinfo()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_enemyRoster;
        break;
      }
      
      // optional .guru.EnemyRoster enemyRoster = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_enemyRoster:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_enemyroster()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_championBans;
        break;
      }
      
      // repeated .guru.ChampionBan championBans = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_championBans:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_championbans()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_championBans;
        if (input->ExpectTag(34)) goto parse_participantState;
        break;
      }
      
      // repeated .guru.MatchupState.ParticipantState participantState = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_participantState:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_participantstate()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_participantState;
        if (input->ExpectTag(42)) goto parse_banSuggestions;
        break;
      }
      
      // optional .guru.BanSuggestions banSuggestions = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_banSuggestions:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_bansuggestions()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(50)) goto parse_participantsSugestions;
        break;
      }
      
      // optional .guru.ParticipantsSuggestions participantsSugestions = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_participantsSugestions:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_participantssugestions()));
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

void MatchupState::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required .guru.MatchupInfo matchupInfo = 1;
  if (has_matchupinfo()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->matchupinfo(), output);
  }
  
  // optional .guru.EnemyRoster enemyRoster = 2;
  if (has_enemyroster()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->enemyroster(), output);
  }
  
  // repeated .guru.ChampionBan championBans = 3;
  for (int i = 0; i < this->championbans_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->championbans(i), output);
  }
  
  // repeated .guru.MatchupState.ParticipantState participantState = 4;
  for (int i = 0; i < this->participantstate_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      4, this->participantstate(i), output);
  }
  
  // optional .guru.BanSuggestions banSuggestions = 5;
  if (has_bansuggestions()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      5, this->bansuggestions(), output);
  }
  
  // optional .guru.ParticipantsSuggestions participantsSugestions = 6;
  if (has_participantssugestions()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      6, this->participantssugestions(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* MatchupState::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required .guru.MatchupInfo matchupInfo = 1;
  if (has_matchupinfo()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->matchupinfo(), target);
  }
  
  // optional .guru.EnemyRoster enemyRoster = 2;
  if (has_enemyroster()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->enemyroster(), target);
  }
  
  // repeated .guru.ChampionBan championBans = 3;
  for (int i = 0; i < this->championbans_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->championbans(i), target);
  }
  
  // repeated .guru.MatchupState.ParticipantState participantState = 4;
  for (int i = 0; i < this->participantstate_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        4, this->participantstate(i), target);
  }
  
  // optional .guru.BanSuggestions banSuggestions = 5;
  if (has_bansuggestions()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        5, this->bansuggestions(), target);
  }
  
  // optional .guru.ParticipantsSuggestions participantsSugestions = 6;
  if (has_participantssugestions()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        6, this->participantssugestions(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int MatchupState::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required .guru.MatchupInfo matchupInfo = 1;
    if (has_matchupinfo()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->matchupinfo());
    }
    
    // optional .guru.EnemyRoster enemyRoster = 2;
    if (has_enemyroster()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->enemyroster());
    }
    
    // optional .guru.BanSuggestions banSuggestions = 5;
    if (has_bansuggestions()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->bansuggestions());
    }
    
    // optional .guru.ParticipantsSuggestions participantsSugestions = 6;
    if (has_participantssugestions()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->participantssugestions());
    }
    
  }
  // repeated .guru.ChampionBan championBans = 3;
  total_size += 1 * this->championbans_size();
  for (int i = 0; i < this->championbans_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->championbans(i));
  }
  
  // repeated .guru.MatchupState.ParticipantState participantState = 4;
  total_size += 1 * this->participantstate_size();
  for (int i = 0; i < this->participantstate_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->participantstate(i));
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

void MatchupState::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const MatchupState* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const MatchupState*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void MatchupState::MergeFrom(const MatchupState& from) {
  GOOGLE_CHECK_NE(&from, this);
  championbans_.MergeFrom(from.championbans_);
  participantstate_.MergeFrom(from.participantstate_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_matchupinfo()) {
      mutable_matchupinfo()->::guru::MatchupInfo::MergeFrom(from.matchupinfo());
    }
    if (from.has_enemyroster()) {
      mutable_enemyroster()->::guru::EnemyRoster::MergeFrom(from.enemyroster());
    }
    if (from.has_bansuggestions()) {
      mutable_bansuggestions()->::guru::BanSuggestions::MergeFrom(from.bansuggestions());
    }
    if (from.has_participantssugestions()) {
      mutable_participantssugestions()->::guru::ParticipantsSuggestions::MergeFrom(from.participantssugestions());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void MatchupState::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MatchupState::CopyFrom(const MatchupState& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MatchupState::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;
  
  if (has_matchupinfo()) {
    if (!this->matchupinfo().IsInitialized()) return false;
  }
  for (int i = 0; i < championbans_size(); i++) {
    if (!this->championbans(i).IsInitialized()) return false;
  }
  for (int i = 0; i < participantstate_size(); i++) {
    if (!this->participantstate(i).IsInitialized()) return false;
  }
  if (has_bansuggestions()) {
    if (!this->bansuggestions().IsInitialized()) return false;
  }
  if (has_participantssugestions()) {
    if (!this->participantssugestions().IsInitialized()) return false;
  }
  return true;
}

void MatchupState::Swap(MatchupState* other) {
  if (other != this) {
    std::swap(matchupinfo_, other->matchupinfo_);
    std::swap(enemyroster_, other->enemyroster_);
    championbans_.Swap(&other->championbans_);
    participantstate_.Swap(&other->participantstate_);
    std::swap(bansuggestions_, other->bansuggestions_);
    std::swap(participantssugestions_, other->participantssugestions_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata MatchupState::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = MatchupState_descriptor_;
  metadata.reflection = MatchupState_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace guru

// @@protoc_insertion_point(global_scope)
