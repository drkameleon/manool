// lib-base-ops-misc.cc -- operations on miscellaneous data supported by base facilities

/*    Copyright (C) 2018, 2019, 2020 Alexey Protasov (AKA Alex or rusini)

   This file is part of MANOOL.

   MANOOL is free software: you can redistribute it and/or modify it under the terms of the version 3 of the GNU General Public License
   as published by the Free Software Foundation (and only version 3).

   MANOOL is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along with MANOOL.  If not, see <https://www.gnu.org/licenses/>.  */


# include "config.tcc"
# include "mnl-lib-base.hh"
# include "base.tcc"

# include <algorithm> // swap_ranges

namespace MNL_AUX_UUID { using namespace aux;

   // Custom ADTs //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   object::~object() {
      if (MNL_UNLIKELY(cleanup)) try {
         auto saved_heap_res = heap_reserve(0), saved_stk_res = stk_reserve(0);
         auto saved_sig_state = move(sig_state); sig_state.first = {};
         if (MNL_LIKELY(sig_trace.empty()))
            move(cleanup)(object{move(*this), move(methods)}); // in the rare case that this throws, the stack trace will be empty
         else {
            auto saved_sig_trace = move(sig_trace); sig_trace.clear(), sig_trace.reserve(saved_sig_trace.capacity()); // ditto
            move(cleanup)(object{move(*this), move(methods)}); // ditto
            sig_trace = move(saved_sig_trace);
         }
         sig_state = move(saved_sig_state);
         heap_reserve(saved_heap_res), stk_reserve(saved_stk_res);
      } MNL_CATCH_UNEXPECTED
   }
   object::object(_record<> &&attribs, shared_ptr<const _record<>> &&methods) noexcept
      : _record<>(move(attribs)), methods(move(methods)) {}

   val object::invoke(val &&self, const sym &op, int argc, val argv[], val *argv_out) {
      switch (!methods->has(op) << 31u | argc << 1u | !!argv_out) { // bit pattern: HCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCO
      // no output parameters requested
      case 0 << 1 | false: // no arguments
         return (*methods)[op](move(self));
      case 1 << 1 | false: // 1 argument
         {  val _argv[]{move(self), move(argv[0])};
            return (*methods)[op](std::extent<decltype(_argv)>::value, _argv);
         }
      case 2 << 1 | false: // 2 arguments
         {  val _argv[]{move(self), move(argv[0]), move(argv[1])};
            return (*methods)[op](std::extent<decltype(_argv)>::value, _argv);
         }
      case 3 << 1 | false: // 3 arguments
         {  val _argv[]{move(self), move(argv[0]), move(argv[1]), move(argv[2])};
            return (*methods)[op](std::extent<decltype(_argv)>::value, _argv);
         }
      case 4 << 1 | false: // 4 arguments
         {  val _argv[]{move(self), move(argv[0]), move(argv[1]), move(argv[2]), move(argv[3])};
            return (*methods)[op](std::extent<decltype(_argv)>::value, _argv);
         }
      case 5 << 1 | false: // 5 arguments
         {  val _argv[]{move(self), move(argv[0]), move(argv[1]), move(argv[2]), move(argv[3]), move(argv[4])};
            return (*methods)[op](std::extent<decltype(_argv)>::value, _argv);
         }
      case 6 << 1 | false: // 6 arguments
         {  val _argv[]{move(self), move(argv[0]), move(argv[1]), move(argv[2]), move(argv[3]), move(argv[4]), move(argv[5])};
            return (*methods)[op](std::extent<decltype(_argv)>::value, _argv);
         }
      case 7 << 1 | false: // 7 arguments
         {  val _argv[]{move(self), move(argv[0]), move(argv[1]), move(argv[2]), move(argv[3]), move(argv[4]), move(argv[5]), move(argv[6])};
            return (*methods)[op](std::extent<decltype(_argv)>::value, _argv);
         }
      case 8 << 1 | false: // 8 arguments
         {  val _argv[]{move(self), move(argv[0]), move(argv[1]), move(argv[2]), move(argv[3]), move(argv[4]), move(argv[5]), move(argv[6]), move(argv[7])};
            return (*methods)[op](std::extent<decltype(_argv)>::value, _argv);
         }
      // output parameters requested
      case 1 << 1 | true: return [&]()->val // 1 argument
         {  val _argv_out[2],
                _argv[]{move(self), move(argv[0])},
                res = (*methods)[op](std::extent<decltype(_argv)>::value, _argv, _argv_out);
            argv_out[0].swap(_argv_out[1]);
            return res;
         }();
      case 2 << 1 | true: return [&]()->val // 2 arguments
         {  val _argv_out[3],
                _argv[]{move(self), move(argv[0]), move(argv[1])},
                res = (*methods)[op](std::extent<decltype(_argv)>::value, _argv, _argv_out);
            argv_out[0].swap(_argv_out[1]), argv_out[1].swap(_argv_out[2]);
            return res;
         }();
      case 3 << 1 | true: return [&]()->val // 3 arguments
         {  val _argv_out[4],
                _argv[]{move(self), move(argv[0]), move(argv[1]), move(argv[2])},
                res = (*methods)[op](std::extent<decltype(_argv)>::value, _argv, _argv_out);
            argv_out[0].swap(_argv_out[1]), argv_out[1].swap(_argv_out[2]), argv_out[2].swap(_argv_out[3]);
            return res;
         }();
      case 4 << 1 | true: return [&]()->val // 4 arguments
         {  val _argv_out[5],
                _argv[]{move(self), move(argv[0]), move(argv[1]), move(argv[2]), move(argv[3])},
                res = (*methods)[op](std::extent<decltype(_argv)>::value, _argv, _argv_out);
            argv_out[0].swap(_argv_out[1]), argv_out[1].swap(_argv_out[2]), argv_out[2].swap(_argv_out[3]), argv_out[3].swap(_argv_out[4]);
            return res;
         }();
      case 5 << 1 | true: return [&]()->val // 5 arguments
         {  val _argv_out[6],
                _argv[]{move(self), move(argv[0]), move(argv[1]), move(argv[2]), move(argv[3]), move(argv[4])},
                res = (*methods)[op](std::extent<decltype(_argv)>::value, _argv, _argv_out);
            argv_out[0].swap(_argv_out[1]), argv_out[1].swap(_argv_out[2]), argv_out[2].swap(_argv_out[3]), argv_out[3].swap(_argv_out[4]),
            argv_out[4].swap(_argv_out[5]);
            return res;
         }();
      case 6 << 1 | true: return [&]()->val // 6 arguments
         {  val _argv_out[7],
                _argv[]{move(self), move(argv[0]), move(argv[1]), move(argv[2]), move(argv[3]), move(argv[4]), move(argv[5])},
                res = (*methods)[op](std::extent<decltype(_argv)>::value, _argv, _argv_out);
            argv_out[0].swap(_argv_out[1]), argv_out[1].swap(_argv_out[2]), argv_out[2].swap(_argv_out[3]), argv_out[3].swap(_argv_out[4]),
            argv_out[4].swap(_argv_out[5]), argv_out[5].swap(_argv_out[6]);
            return res;
         }();
      case 7 << 1 | true: return [&]()->val // 7 arguments
         {  val _argv_out[8],
                _argv[]{move(self), move(argv[0]), move(argv[1]), move(argv[2]), move(argv[3]), move(argv[4]), move(argv[5]), move(argv[6])},
                res = (*methods)[op](std::extent<decltype(_argv)>::value, _argv, _argv_out);
            argv_out[0].swap(_argv_out[1]), argv_out[1].swap(_argv_out[2]), argv_out[2].swap(_argv_out[3]), argv_out[3].swap(_argv_out[4]),
            argv_out[4].swap(_argv_out[5]), argv_out[5].swap(_argv_out[6]), argv_out[6].swap(_argv_out[7]);
            return res;
         }();
      case 8 << 1 | true: return [&]()->val // 8 arguments
         {  val _argv_out[9],
                _argv[]{move(self), move(argv[0]), move(argv[1]), move(argv[2]), move(argv[3]), move(argv[4]), move(argv[5]), move(argv[6]), move(argv[7])},
                res = (*methods)[op](std::extent<decltype(_argv)>::value, _argv, _argv_out);
            argv_out[0].swap(_argv_out[1]), argv_out[1].swap(_argv_out[2]), argv_out[2].swap(_argv_out[3]), argv_out[3].swap(_argv_out[4]),
            argv_out[4].swap(_argv_out[5]), argv_out[5].swap(_argv_out[6]), argv_out[6].swap(_argv_out[7]), argv_out[7].swap(_argv_out[8]);
            return res;
         }();
      }
      if (MNL_UNLIKELY(!methods->has(op)))
         return self.default_invoke(op, argc, argv);
      // more than 8 arguments
      if (MNL_UNLIKELY(argc + 1 > val::max_argc))
         MNL_ERR(MNL_SYM("LimitExceeded"));
      stk_check();
      if (MNL_LIKELY(!argv_out)) {
         val _argv[argc + 1];
         self.swap(_argv[0]); std::swap_ranges(argv, argv + argc, _argv + 1);
         return (*methods)[op](argc + 1, _argv);
      }
      return [&]()->val{
         val _argv_out[argc + 1], _argv[argc + 1];
         self.swap(_argv[0]); std::swap_ranges(argv, argv + argc, _argv + 1);
         val res = (*methods)[op](argc + 1, _argv, _argv_out);
         std::swap_ranges(argv_out, argv_out + argc, _argv_out + 1);
         return res;
      }();
   }

   template class box<object>;

   // MANOOL Pointers //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   s_pointer::~s_pointer() {
      if (MNL_LIKELY(!cleanup)) {
         if (weak) MNL_IF_WITH_MT(std::lock_guard<std::mutex>(cast<w_pointer &>(weak).mutex),) cast<w_pointer &>(weak).value = {};
      } else try {
         auto saved_heap_res = heap_reserve(0), saved_stk_res = stk_reserve(0);
         auto saved_sig_state = move(sig_state); sig_state.first = {};
         if (MNL_LIKELY(sig_trace.empty())) {
            if (!weak) weak = w_pointer{&value MNL_IF_WITH_MT(,mutex)}; // in the rare case that this throws, the stack trace will be empty
            move(cleanup)(weak); // ditto
         } else {
            auto saved_sig_trace = move(sig_trace); sig_trace.clear(), sig_trace.reserve(saved_sig_trace.capacity()); // ditto
            if (!weak) weak = w_pointer{&value MNL_IF_WITH_MT(,mutex)}; // ditto
            move(cleanup)(weak); // ditto
            sig_trace = move(saved_sig_trace);
         }
         sig_state = move(saved_sig_state);
         heap_reserve(saved_heap_res), stk_reserve(saved_stk_res);
         MNL_IF_WITH_MT(std::lock_guard<std::mutex>(cast<w_pointer &>(weak).mutex),) cast<w_pointer &>(weak).value = {};
      } MNL_CATCH_UNEXPECTED
   }
   val w_pointer::invoke(val &&self, const sym &op, int argc, val argv[], val *argv_out) const {
      switch (MNL_DISP("^", "Set", "Weak", "Order", "Str")[op]) {
      case 1: // ^
         if (MNL_UNLIKELY(argc != 0)) MNL_ERR(MNL_SYM("InvalidInvocation"));
         MNL_IF_WITH_MT( return std::lock_guard<std::mutex>{mutex}, [&]{ )
            if (MNL_UNLIKELY(!value)) MNL_ERR(MNL_SYM("DanglingPointer"));
            return MNL_IF_WITH_MT(std::lock_guard<std::mutex>{val_mutex},) *value;
         MNL_IF_WITH_MT( }(); )
      case 2: // Set
         if (MNL_UNLIKELY(argc != 1)) MNL_ERR(MNL_SYM("InvalidInvocation"));
         MNL_IF_WITH_MT( std::lock_guard<std::mutex>{mutex}, [&]{ )
            if (MNL_UNLIKELY(!value)) MNL_ERR(MNL_SYM("DanglingPointer"));
            MNL_IF_WITH_MT(std::lock_guard<std::mutex>{val_mutex},) argv[0].swap(*value);
         MNL_IF_WITH_MT( }(); )
         if (MNL_UNLIKELY(argv_out)) argv[0].swap(argv_out[0]); return {};
      case 3: // Weak
         if (MNL_UNLIKELY(argc != 0)) MNL_ERR(MNL_SYM("InvalidInvocation"));
         return move(self);
      case 4: // Order
         if (MNL_UNLIKELY(argc != 1)) MNL_ERR(MNL_SYM("InvalidInvocation"));
         if (MNL_UNLIKELY(!test<w_pointer>(argv[0]))) return self.default_order(argv[0]);
         {  auto mask = MNL_AUX_RAND(uintptr_t);
            return
               ((reinterpret_cast<uintptr_t>(this) ^ mask) > (reinterpret_cast<uintptr_t>(&cast<const w_pointer &>(argv[0])) ^ mask)) -
               ((reinterpret_cast<uintptr_t>(this) ^ mask) < (reinterpret_cast<uintptr_t>(&cast<const w_pointer &>(argv[0])) ^ mask));
         }
      case 5: // Str
         if (MNL_UNLIKELY(argc != 0)) MNL_ERR(MNL_SYM("InvalidInvocation"));
         {  char buf[sizeof "weak pointer 18446744073709551615"];
            return sprintf(buf, "weak pointer %llu", (unsigned long long)reinterpret_cast<uintptr_t>(this) ^ MNL_AUX_RAND(uintptr_t)), buf;
         }
      case 0: return self.default_invoke(op, argc, argv);
      }
   }
   val s_pointer::invoke(val &&self, const sym &op, int argc, val argv[], val *argv_out) {
      switch (MNL_DISP("^", "RefCount", "Set", "Weak", "Order", "Str")[op]) {
      case 1: // ^
         if (MNL_UNLIKELY(argc != 0)) MNL_ERR(MNL_SYM("InvalidInvocation"));
         return MNL_IF_WITH_MT(std::lock_guard<std::mutex>{mutex},) value;
      case 2: // RefCount
         if (MNL_UNLIKELY(argc != 0)) MNL_ERR(MNL_SYM("InvalidInvocation"));
         return (long long)(self.rc() - 1);
      case 3: // Set
         if (MNL_UNLIKELY(argc != 1)) MNL_ERR(MNL_SYM("InvalidInvocation"));
         MNL_IF_WITH_MT(std::lock_guard<std::mutex>{mutex},) argv[0].swap(value);
         if (MNL_UNLIKELY(argv_out)) argv[0].swap(argv_out[0]); return {};
      case 4: // Weak
         if (MNL_UNLIKELY(argc != 0)) MNL_ERR(MNL_SYM("InvalidInvocation"));
         MNL_IF_WITH_MT( std::lock_guard<std::mutex>{mutex}, [&]{ )
            if (MNL_UNLIKELY(!weak)) weak = w_pointer{&value MNL_IF_WITH_MT(,mutex)};
         MNL_IF_WITH_MT( }(); )
         return weak;
      case 5: // Order
         if (MNL_UNLIKELY(argc != 1)) MNL_ERR(MNL_SYM("InvalidInvocation"));
         if (MNL_UNLIKELY(!test<s_pointer>(argv[0]))) return self.default_order(argv[0]);
         {  auto mask = MNL_AUX_RAND(uintptr_t);
            return
               ((reinterpret_cast<uintptr_t>(this) ^ mask) > (reinterpret_cast<uintptr_t>(&cast<const s_pointer &>(argv[0])) ^ mask)) -
               ((reinterpret_cast<uintptr_t>(this) ^ mask) < (reinterpret_cast<uintptr_t>(&cast<const s_pointer &>(argv[0])) ^ mask));
         }
      case 6: // Str
         if (MNL_UNLIKELY(argc != 0)) MNL_ERR(MNL_SYM("InvalidInvocation"));
         {  char buf[sizeof "strong pointer 18446744073709551615"];
            return sprintf(buf, "strong pointer %llu", (unsigned long long)reinterpret_cast<uintptr_t>(this) ^ MNL_AUX_RAND(uintptr_t)), buf;
         }
      case 0: return self.default_invoke(op, argc, argv);
      }
   }
   template class box<w_pointer>;
   template class box<s_pointer>;

} // namespace MNL_AUX_UUID
