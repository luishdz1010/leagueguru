// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: participantssuggestions.proto

#ifndef PROTOBUF_participantssuggestions_2eproto__INCLUDED
#define PROTOBUF_participantssuggestions_2eproto__INCLUDED

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
#include "participantrole.pb.h"
// @@protoc_insertion_point(includes)

namespace guru {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_participantssuggestions_2eproto();
void protobuf_AssignDesc_participantssuggestions_2eproto();
void protobuf_ShutdownFile_participantssuggestions_2eproto();

class ParticipantSuggestions;
class ParticipantSuggestions_Suggestion;
class ParticipantSuggestions_ChampionMatchup;
class ParticipantsSuggestions;

// ===================================================================

class ParticipantSuggestions_Suggestion : public ::google::protobuf::Message {
 public:
  ParticipantSuggestions_Suggestion();
  virtual ~ParticipantSuggestions_Suggestion();
  
  ParticipantSuggestions_Suggestion(const ParticipantSuggestions_Suggestion& from);
  
  inline ParticipantSuggestions_Suggestion& operator=(const ParticipantSuggestions_Suggestion& from) {
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
  static const ParticipantSuggestions_Suggestion& default_instance();
  
  void Swap(ParticipantSuggestions_Suggestion* other);
  
  // implements Message ----------------------------------------------
  
  ParticipantSuggestions_Suggestion* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ParticipantSuggestions_Suggestion& from);
  void MergeFrom(const ParticipantSuggestions_Suggestion& from);
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
  
  // required uint32 championId = 1;
  inline bool has_championid() const;
  inline void clear_championid();
  static const int kChampionIdFieldNumber = 1;
  inline ::google::protobuf::uint32 championid() const;
  inline void set_championid(::google::protobuf::uint32 value);
  
  // required .guru.ChampionRole role = 2;
  inline bool has_role() const;
  inline void clear_role();
  static const int kRoleFieldNumber = 2;
  inline guru::ChampionRole role() const;
  inline void set_role(guru::ChampionRole value);
  
  // repeated .guru.ParticipantSuggestions.ChampionMatchup strongAgainst = 3;
  inline int strongagainst_size() const;
  inline void clear_strongagainst();
  static const int kStrongAgainstFieldNumber = 3;
  inline const ::guru::ParticipantSuggestions_ChampionMatchup& strongagainst(int index) const;
  inline ::guru::ParticipantSuggestions_ChampionMatchup* mutable_strongagainst(int index);
  inline ::guru::ParticipantSuggestions_ChampionMatchup* add_strongagainst();
  inline const ::google::protobuf::RepeatedPtrField< ::guru::ParticipantSuggestions_ChampionMatchup >&
      strongagainst() const;
  inline ::google::protobuf::RepeatedPtrField< ::guru::ParticipantSuggestions_ChampionMatchup >*
      mutable_strongagainst();
  
  // repeated .guru.ParticipantSuggestions.ChampionMatchup badAgainst = 4;
  inline int badagainst_size() const;
  inline void clear_badagainst();
  static const int kBadAgainstFieldNumber = 4;
  inline const ::guru::ParticipantSuggestions_ChampionMatchup& badagainst(int index) const;
  inline ::guru::ParticipantSuggestions_ChampionMatchup* mutable_badagainst(int index);
  inline ::guru::ParticipantSuggestions_ChampionMatchup* add_badagainst();
  inline const ::google::protobuf::RepeatedPtrField< ::guru::ParticipantSuggestions_ChampionMatchup >&
      badagainst() const;
  inline ::google::protobuf::RepeatedPtrField< ::guru::ParticipantSuggestions_ChampionMatchup >*
      mutable_badagainst();
  
  // repeated .guru.ParticipantSuggestions.ChampionMatchup goodWith = 5;
  inline int goodwith_size() const;
  inline void clear_goodwith();
  static const int kGoodWithFieldNumber = 5;
  inline const ::guru::ParticipantSuggestions_ChampionMatchup& goodwith(int index) const;
  inline ::guru::ParticipantSuggestions_ChampionMatchup* mutable_goodwith(int index);
  inline ::guru::ParticipantSuggestions_ChampionMatchup* add_goodwith();
  inline const ::google::protobuf::RepeatedPtrField< ::guru::ParticipantSuggestions_ChampionMatchup >&
      goodwith() const;
  inline ::google::protobuf::RepeatedPtrField< ::guru::ParticipantSuggestions_ChampionMatchup >*
      mutable_goodwith();
  
  // @@protoc_insertion_point(class_scope:guru.ParticipantSuggestions.Suggestion)
 private:
  inline void set_has_championid();
  inline void clear_has_championid();
  inline void set_has_role();
  inline void clear_has_role();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::uint32 championid_;
  int role_;
  ::google::protobuf::RepeatedPtrField< ::guru::ParticipantSuggestions_ChampionMatchup > strongagainst_;
  ::google::protobuf::RepeatedPtrField< ::guru::ParticipantSuggestions_ChampionMatchup > badagainst_;
  ::google::protobuf::RepeatedPtrField< ::guru::ParticipantSuggestions_ChampionMatchup > goodwith_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(5 + 31) / 32];
  
  friend void  protobuf_AddDesc_participantssuggestions_2eproto();
  friend void protobuf_AssignDesc_participantssuggestions_2eproto();
  friend void protobuf_ShutdownFile_participantssuggestions_2eproto();
  
  void InitAsDefaultInstance();
  static ParticipantSuggestions_Suggestion* default_instance_;
};
// -------------------------------------------------------------------

class ParticipantSuggestions_ChampionMatchup : public ::google::protobuf::Message {
 public:
  ParticipantSuggestions_ChampionMatchup();
  virtual ~ParticipantSuggestions_ChampionMatchup();
  
  ParticipantSuggestions_ChampionMatchup(const ParticipantSuggestions_ChampionMatchup& from);
  
  inline ParticipantSuggestions_ChampionMatchup& operator=(const ParticipantSuggestions_ChampionMatchup& from) {
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
  static const ParticipantSuggestions_ChampionMatchup& default_instance();
  
  void Swap(ParticipantSuggestions_ChampionMatchup* other);
  
  // implements Message ----------------------------------------------
  
  ParticipantSuggestions_ChampionMatchup* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ParticipantSuggestions_ChampionMatchup& from);
  void MergeFrom(const ParticipantSuggestions_ChampionMatchup& from);
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
  
  // required uint32 championId = 1;
  inline bool has_championid() const;
  inline void clear_championid();
  static const int kChampionIdFieldNumber = 1;
  inline ::google::protobuf::uint32 championid() const;
  inline void set_championid(::google::protobuf::uint32 value);
  
  // required double winrate = 2;
  inline bool has_winrate() const;
  inline void clear_winrate();
  static const int kWinrateFieldNumber = 2;
  inline double winrate() const;
  inline void set_winrate(double value);
  
  // @@protoc_insertion_point(class_scope:guru.ParticipantSuggestions.ChampionMatchup)
 private:
  inline void set_has_championid();
  inline void clear_has_championid();
  inline void set_has_winrate();
  inline void clear_has_winrate();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  double winrate_;
  ::google::protobuf::uint32 championid_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_participantssuggestions_2eproto();
  friend void protobuf_AssignDesc_participantssuggestions_2eproto();
  friend void protobuf_ShutdownFile_participantssuggestions_2eproto();
  
  void InitAsDefaultInstance();
  static ParticipantSuggestions_ChampionMatchup* default_instance_;
};
// -------------------------------------------------------------------

class ParticipantSuggestions : public ::google::protobuf::Message {
 public:
  ParticipantSuggestions();
  virtual ~ParticipantSuggestions();
  
  ParticipantSuggestions(const ParticipantSuggestions& from);
  
  inline ParticipantSuggestions& operator=(const ParticipantSuggestions& from) {
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
  static const ParticipantSuggestions& default_instance();
  
  void Swap(ParticipantSuggestions* other);
  
  // implements Message ----------------------------------------------
  
  ParticipantSuggestions* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ParticipantSuggestions& from);
  void MergeFrom(const ParticipantSuggestions& from);
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
  
  typedef ParticipantSuggestions_Suggestion Suggestion;
  typedef ParticipantSuggestions_ChampionMatchup ChampionMatchup;
  
  // accessors -------------------------------------------------------
  
  // required uint32 participant = 1;
  inline bool has_participant() const;
  inline void clear_participant();
  static const int kParticipantFieldNumber = 1;
  inline ::google::protobuf::uint32 participant() const;
  inline void set_participant(::google::protobuf::uint32 value);
  
  // repeated .guru.ParticipantSuggestions.Suggestion champions = 2;
  inline int champions_size() const;
  inline void clear_champions();
  static const int kChampionsFieldNumber = 2;
  inline const ::guru::ParticipantSuggestions_Suggestion& champions(int index) const;
  inline ::guru::ParticipantSuggestions_Suggestion* mutable_champions(int index);
  inline ::guru::ParticipantSuggestions_Suggestion* add_champions();
  inline const ::google::protobuf::RepeatedPtrField< ::guru::ParticipantSuggestions_Suggestion >&
      champions() const;
  inline ::google::protobuf::RepeatedPtrField< ::guru::ParticipantSuggestions_Suggestion >*
      mutable_champions();
  
  // @@protoc_insertion_point(class_scope:guru.ParticipantSuggestions)
 private:
  inline void set_has_participant();
  inline void clear_has_participant();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::guru::ParticipantSuggestions_Suggestion > champions_;
  ::google::protobuf::uint32 participant_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_participantssuggestions_2eproto();
  friend void protobuf_AssignDesc_participantssuggestions_2eproto();
  friend void protobuf_ShutdownFile_participantssuggestions_2eproto();
  
  void InitAsDefaultInstance();
  static ParticipantSuggestions* default_instance_;
};
// -------------------------------------------------------------------

class ParticipantsSuggestions : public ::google::protobuf::Message {
 public:
  ParticipantsSuggestions();
  virtual ~ParticipantsSuggestions();
  
  ParticipantsSuggestions(const ParticipantsSuggestions& from);
  
  inline ParticipantsSuggestions& operator=(const ParticipantsSuggestions& from) {
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
  static const ParticipantsSuggestions& default_instance();
  
  void Swap(ParticipantsSuggestions* other);
  
  // implements Message ----------------------------------------------
  
  ParticipantsSuggestions* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ParticipantsSuggestions& from);
  void MergeFrom(const ParticipantsSuggestions& from);
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
  
  // repeated .guru.ParticipantSuggestions suggestions = 1;
  inline int suggestions_size() const;
  inline void clear_suggestions();
  static const int kSuggestionsFieldNumber = 1;
  inline const ::guru::ParticipantSuggestions& suggestions(int index) const;
  inline ::guru::ParticipantSuggestions* mutable_suggestions(int index);
  inline ::guru::ParticipantSuggestions* add_suggestions();
  inline const ::google::protobuf::RepeatedPtrField< ::guru::ParticipantSuggestions >&
      suggestions() const;
  inline ::google::protobuf::RepeatedPtrField< ::guru::ParticipantSuggestions >*
      mutable_suggestions();
  
  // @@protoc_insertion_point(class_scope:guru.ParticipantsSuggestions)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::guru::ParticipantSuggestions > suggestions_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_participantssuggestions_2eproto();
  friend void protobuf_AssignDesc_participantssuggestions_2eproto();
  friend void protobuf_ShutdownFile_participantssuggestions_2eproto();
  
  void InitAsDefaultInstance();
  static ParticipantsSuggestions* default_instance_;
};
// ===================================================================


// ===================================================================

// ParticipantSuggestions_Suggestion

// required uint32 championId = 1;
inline bool ParticipantSuggestions_Suggestion::has_championid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ParticipantSuggestions_Suggestion::set_has_championid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ParticipantSuggestions_Suggestion::clear_has_championid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ParticipantSuggestions_Suggestion::clear_championid() {
  championid_ = 0u;
  clear_has_championid();
}
inline ::google::protobuf::uint32 ParticipantSuggestions_Suggestion::championid() const {
  return championid_;
}
inline void ParticipantSuggestions_Suggestion::set_championid(::google::protobuf::uint32 value) {
  set_has_championid();
  championid_ = value;
}

// required .guru.ChampionRole role = 2;
inline bool ParticipantSuggestions_Suggestion::has_role() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ParticipantSuggestions_Suggestion::set_has_role() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ParticipantSuggestions_Suggestion::clear_has_role() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ParticipantSuggestions_Suggestion::clear_role() {
  role_ = 0;
  clear_has_role();
}
inline guru::ChampionRole ParticipantSuggestions_Suggestion::role() const {
  return static_cast< guru::ChampionRole >(role_);
}
inline void ParticipantSuggestions_Suggestion::set_role(guru::ChampionRole value) {
  GOOGLE_DCHECK(guru::ChampionRole_IsValid(value));
  set_has_role();
  role_ = value;
}

// repeated .guru.ParticipantSuggestions.ChampionMatchup strongAgainst = 3;
inline int ParticipantSuggestions_Suggestion::strongagainst_size() const {
  return strongagainst_.size();
}
inline void ParticipantSuggestions_Suggestion::clear_strongagainst() {
  strongagainst_.Clear();
}
inline const ::guru::ParticipantSuggestions_ChampionMatchup& ParticipantSuggestions_Suggestion::strongagainst(int index) const {
  return strongagainst_.Get(index);
}
inline ::guru::ParticipantSuggestions_ChampionMatchup* ParticipantSuggestions_Suggestion::mutable_strongagainst(int index) {
  return strongagainst_.Mutable(index);
}
inline ::guru::ParticipantSuggestions_ChampionMatchup* ParticipantSuggestions_Suggestion::add_strongagainst() {
  return strongagainst_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::guru::ParticipantSuggestions_ChampionMatchup >&
ParticipantSuggestions_Suggestion::strongagainst() const {
  return strongagainst_;
}
inline ::google::protobuf::RepeatedPtrField< ::guru::ParticipantSuggestions_ChampionMatchup >*
ParticipantSuggestions_Suggestion::mutable_strongagainst() {
  return &strongagainst_;
}

// repeated .guru.ParticipantSuggestions.ChampionMatchup badAgainst = 4;
inline int ParticipantSuggestions_Suggestion::badagainst_size() const {
  return badagainst_.size();
}
inline void ParticipantSuggestions_Suggestion::clear_badagainst() {
  badagainst_.Clear();
}
inline const ::guru::ParticipantSuggestions_ChampionMatchup& ParticipantSuggestions_Suggestion::badagainst(int index) const {
  return badagainst_.Get(index);
}
inline ::guru::ParticipantSuggestions_ChampionMatchup* ParticipantSuggestions_Suggestion::mutable_badagainst(int index) {
  return badagainst_.Mutable(index);
}
inline ::guru::ParticipantSuggestions_ChampionMatchup* ParticipantSuggestions_Suggestion::add_badagainst() {
  return badagainst_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::guru::ParticipantSuggestions_ChampionMatchup >&
ParticipantSuggestions_Suggestion::badagainst() const {
  return badagainst_;
}
inline ::google::protobuf::RepeatedPtrField< ::guru::ParticipantSuggestions_ChampionMatchup >*
ParticipantSuggestions_Suggestion::mutable_badagainst() {
  return &badagainst_;
}

// repeated .guru.ParticipantSuggestions.ChampionMatchup goodWith = 5;
inline int ParticipantSuggestions_Suggestion::goodwith_size() const {
  return goodwith_.size();
}
inline void ParticipantSuggestions_Suggestion::clear_goodwith() {
  goodwith_.Clear();
}
inline const ::guru::ParticipantSuggestions_ChampionMatchup& ParticipantSuggestions_Suggestion::goodwith(int index) const {
  return goodwith_.Get(index);
}
inline ::guru::ParticipantSuggestions_ChampionMatchup* ParticipantSuggestions_Suggestion::mutable_goodwith(int index) {
  return goodwith_.Mutable(index);
}
inline ::guru::ParticipantSuggestions_ChampionMatchup* ParticipantSuggestions_Suggestion::add_goodwith() {
  return goodwith_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::guru::ParticipantSuggestions_ChampionMatchup >&
ParticipantSuggestions_Suggestion::goodwith() const {
  return goodwith_;
}
inline ::google::protobuf::RepeatedPtrField< ::guru::ParticipantSuggestions_ChampionMatchup >*
ParticipantSuggestions_Suggestion::mutable_goodwith() {
  return &goodwith_;
}

// -------------------------------------------------------------------

// ParticipantSuggestions_ChampionMatchup

// required uint32 championId = 1;
inline bool ParticipantSuggestions_ChampionMatchup::has_championid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ParticipantSuggestions_ChampionMatchup::set_has_championid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ParticipantSuggestions_ChampionMatchup::clear_has_championid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ParticipantSuggestions_ChampionMatchup::clear_championid() {
  championid_ = 0u;
  clear_has_championid();
}
inline ::google::protobuf::uint32 ParticipantSuggestions_ChampionMatchup::championid() const {
  return championid_;
}
inline void ParticipantSuggestions_ChampionMatchup::set_championid(::google::protobuf::uint32 value) {
  set_has_championid();
  championid_ = value;
}

// required double winrate = 2;
inline bool ParticipantSuggestions_ChampionMatchup::has_winrate() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ParticipantSuggestions_ChampionMatchup::set_has_winrate() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ParticipantSuggestions_ChampionMatchup::clear_has_winrate() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ParticipantSuggestions_ChampionMatchup::clear_winrate() {
  winrate_ = 0;
  clear_has_winrate();
}
inline double ParticipantSuggestions_ChampionMatchup::winrate() const {
  return winrate_;
}
inline void ParticipantSuggestions_ChampionMatchup::set_winrate(double value) {
  set_has_winrate();
  winrate_ = value;
}

// -------------------------------------------------------------------

// ParticipantSuggestions

// required uint32 participant = 1;
inline bool ParticipantSuggestions::has_participant() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ParticipantSuggestions::set_has_participant() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ParticipantSuggestions::clear_has_participant() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ParticipantSuggestions::clear_participant() {
  participant_ = 0u;
  clear_has_participant();
}
inline ::google::protobuf::uint32 ParticipantSuggestions::participant() const {
  return participant_;
}
inline void ParticipantSuggestions::set_participant(::google::protobuf::uint32 value) {
  set_has_participant();
  participant_ = value;
}

// repeated .guru.ParticipantSuggestions.Suggestion champions = 2;
inline int ParticipantSuggestions::champions_size() const {
  return champions_.size();
}
inline void ParticipantSuggestions::clear_champions() {
  champions_.Clear();
}
inline const ::guru::ParticipantSuggestions_Suggestion& ParticipantSuggestions::champions(int index) const {
  return champions_.Get(index);
}
inline ::guru::ParticipantSuggestions_Suggestion* ParticipantSuggestions::mutable_champions(int index) {
  return champions_.Mutable(index);
}
inline ::guru::ParticipantSuggestions_Suggestion* ParticipantSuggestions::add_champions() {
  return champions_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::guru::ParticipantSuggestions_Suggestion >&
ParticipantSuggestions::champions() const {
  return champions_;
}
inline ::google::protobuf::RepeatedPtrField< ::guru::ParticipantSuggestions_Suggestion >*
ParticipantSuggestions::mutable_champions() {
  return &champions_;
}

// -------------------------------------------------------------------

// ParticipantsSuggestions

// repeated .guru.ParticipantSuggestions suggestions = 1;
inline int ParticipantsSuggestions::suggestions_size() const {
  return suggestions_.size();
}
inline void ParticipantsSuggestions::clear_suggestions() {
  suggestions_.Clear();
}
inline const ::guru::ParticipantSuggestions& ParticipantsSuggestions::suggestions(int index) const {
  return suggestions_.Get(index);
}
inline ::guru::ParticipantSuggestions* ParticipantsSuggestions::mutable_suggestions(int index) {
  return suggestions_.Mutable(index);
}
inline ::guru::ParticipantSuggestions* ParticipantsSuggestions::add_suggestions() {
  return suggestions_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::guru::ParticipantSuggestions >&
ParticipantsSuggestions::suggestions() const {
  return suggestions_;
}
inline ::google::protobuf::RepeatedPtrField< ::guru::ParticipantSuggestions >*
ParticipantsSuggestions::mutable_suggestions() {
  return &suggestions_;
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

#endif  // PROTOBUF_participantssuggestions_2eproto__INCLUDED
