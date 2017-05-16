/* Copyright 2017 Stanford University, NVIDIA Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// instances for Realm

#ifndef REALM_INSTANCE_INL
#define REALM_INSTANCE_INL

// nop, but helps IDEs
#include "instance.h"

#include "indexspace.h"
#include "inst_layout.h"
#include "serialize.h"

TYPE_IS_SERIALIZABLE(Realm::RegionInstance);

namespace Realm {

  ////////////////////////////////////////////////////////////////////////
  //
  // class RegionInstance

  inline bool RegionInstance::operator<(const RegionInstance& rhs) const
  {
    return id < rhs.id;
  }

  inline bool RegionInstance::operator==(const RegionInstance& rhs) const
  {
    return id == rhs.id;
  }

  inline bool RegionInstance::operator!=(const RegionInstance& rhs) const
  {
    return id != rhs.id;
  }

  inline bool RegionInstance::exists(void) const
  {
    return id != 0;
  }

  inline std::ostream& operator<<(std::ostream& os, RegionInstance r)
  {
    return os << std::hex << r.id << std::dec;
  }

#if 0		
  template <int N, typename T>
  const ZIndexSpace<N,T>& RegionInstance::get_indexspace(void) const
  {
    return get_lis().as_dim<N,T>().indexspace;
  }
		
  template <int N>
  const ZIndexSpace<N,int>& RegionInstance::get_indexspace(void) const
  {
    return get_lis().as_dim<N,int>().indexspace;
  }
#endif
		
  ////////////////////////////////////////////////////////////////////////
  //
  // class RegionInstance

  template <int N, typename T>
  inline /*static*/ RegionInstance RegionInstance::create_instance(Memory memory,
								   const ZIndexSpace<N,T>& space,
								   const std::vector<size_t> &field_sizes,
								   const ProfilingRequestSet& reqs)
  {
    InstanceLayoutConstraints ilc(field_sizes, 0 /*SOA*/);
    InstanceLayoutGeneric *layout = InstanceLayoutGeneric::choose_instance_layout(space, ilc);
#if 0
    delete layout;

    if(N == 1) {
      assert(space.dense());
      LegionRuntime::Arrays::Rect<1> r;
      r.lo = space.bounds.lo.x;
      r.hi = space.bounds.hi.x;
      Domain d = Domain::from_rect<1>(r);
      return d.create_instance(memory, field_sizes, space.bounds.volume(), reqs);
    } else {
      // TODO: all sorts of serialization fun...
      assert(false);
      return RegionInstance::NO_INST;
    }
#endif
    return create_instance(memory, layout, reqs);
  }

  template <int N, typename T>
  inline /*static*/ RegionInstance RegionInstance::create_file_instance(const char *file_name,
									const ZIndexSpace<N,T>& space,
									const std::vector<size_t> &field_sizes,
									legion_lowlevel_file_mode_t file_mode,
									const ProfilingRequestSet& prs)
  {
    assert(0);
    return RegionInstance::NO_INST;
  }

  template <int N, typename T>
  inline /*static*/ RegionInstance RegionInstance::create_hdf5_instance(const char *file_name,
									const ZIndexSpace<N,T>& space,
									const std::vector<size_t> &field_sizes,
									const std::vector<const char*> &field_files,
									bool read_only,
									const ProfilingRequestSet& prs)
  {
    assert(0);
    return RegionInstance::NO_INST;
  }

  template <int N, typename T>
  inline ZIndexSpace<N,T> RegionInstance::get_indexspace(void) const
  {
#if 0
    return get_lis().as_dim<N,T>().indexspace;
#endif
    return ZIndexSpace<N,T>();
  }
		
  template <int N>
  inline ZIndexSpace<N,int> RegionInstance::get_indexspace(void) const
  {
#if 0
    return get_lis().as_dim<N,int>().indexspace;
#endif
    return ZIndexSpace<N,int>();
  }


  ////////////////////////////////////////////////////////////////////////
  //
  // class RegionInstance::DestroyedField


  inline RegionInstance::DestroyedField::DestroyedField(void) 
    : offset(0), size(0), serdez_id(0)
  { }

  inline RegionInstance::DestroyedField::DestroyedField(unsigned o, unsigned s, CustomSerdezID sid)
    : offset(o), size(s), serdez_id(sid)
  { }


}; // namespace Realm  

#endif // ifndef REALM_INSTANCE_INL
