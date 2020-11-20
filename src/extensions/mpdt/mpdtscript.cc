// See www.openfst.org for extensive documentation on this weighted
// finite-state transducer library.
//
// Definitions of 'scriptable' versions of mpdt operations, that is,
// those that can be called with FstClass-type arguments.
//
// See comments in nlp/fst/script/script-impl.h for how the registration
// mechanism allows these to work with various arc types.

#include <fst/extensions/mpdt/mpdtscript.h>

#include <string>
#include <utility>
#include <vector>

#include <fst/types.h>
#include <fst/extensions/mpdt/compose.h>
#include <fst/extensions/mpdt/expand.h>
#include <fst/extensions/mpdt/reverse.h>
#include <fst/script/script-impl.h>

namespace fst {
namespace script {

void MPdtCompose(const FstClass &ifst1, const FstClass &ifst2,
                 const std::vector<std::pair<int64, int64>> &parens,
                 const std::vector<int64> &assignments, MutableFstClass *ofst,
                 const MPdtComposeOptions &copts, bool left_pdt) {
  if (!internal::ArcTypesMatch(ifst1, ifst2, "MPdtCompose") ||
      !internal::ArcTypesMatch(ifst1, *ofst, "MPdtCompose"))
    return;
  MPdtComposeArgs args(ifst1, ifst2, parens, assignments, ofst, copts,
                       left_pdt);
  Apply<Operation<MPdtComposeArgs>>("MPdtCompose", ifst1.ArcType(), &args);
}

REGISTER_FST_OPERATION_3ARCS(MPdtCompose, MPdtComposeArgs);

void MPdtExpand(const FstClass &ifst,
                const std::vector<std::pair<int64, int64>> &parens,
                const std::vector<int64> &assignments, MutableFstClass *ofst,
                const MPdtExpandOptions &opts) {
  MPdtExpandArgs args(ifst, parens, assignments, ofst, opts);
  Apply<Operation<MPdtExpandArgs>>("MPdtExpand", ifst.ArcType(), &args);
}

REGISTER_FST_OPERATION_3ARCS(MPdtExpand, MPdtExpandArgs);

void MPdtExpand(const FstClass &ifst,
                const std::vector<std::pair<int64, int64>> &parens,
                const std::vector<int64> &assignments, MutableFstClass *ofst,
                bool connect) {
  MPdtExpand(ifst, parens, assignments, ofst, MPdtExpandOptions(connect));
}

void MPdtReverse(const FstClass &ifst,
                 const std::vector<std::pair<int64, int64>> &parens,
                 std::vector<int64> *assignments, MutableFstClass *ofst) {
  MPdtReverseArgs args(ifst, parens, assignments, ofst);
  Apply<Operation<MPdtReverseArgs>>("MPdtReverse", ifst.ArcType(), &args);
}

REGISTER_FST_OPERATION_3ARCS(MPdtReverse, MPdtReverseArgs);

void PrintMPdtInfo(const FstClass &ifst,
                   const std::vector<std::pair<int64, int64>> &parens,
                   const std::vector<int64> &assignments) {
  PrintMPdtInfoArgs args(ifst, parens, assignments);
  Apply<Operation<PrintMPdtInfoArgs>>("PrintMPdtInfo", ifst.ArcType(), &args);
}

REGISTER_FST_OPERATION_3ARCS(PrintMPdtInfo, PrintMPdtInfoArgs);

}  // namespace script
}  // namespace fst
