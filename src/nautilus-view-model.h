#ifndef NAUTILUS_VIEW_MODEL_H
#define NAUTILUS_VIEW_MODEL_H

#include <glib.h>
#include "nautilus-file.h"

G_BEGIN_DECLS

#define NAUTILUS_TYPE_VIEW_MODEL (nautilus_view_model_get_type())

G_DECLARE_FINAL_TYPE (NautilusViewModel, nautilus_view_model, NAUTILUS, VIEW_MODEL, GObject)

typedef struct
{
    NautilusFileSortType sort_type;
    gboolean reversed;
    gboolean directories_first;
} NautilusViewModelSortData;

NautilusViewModel * nautilus_view_model_new (void);

void nautilus_view_model_set_sort_type (NautilusViewModel         *self,
                                        NautilusViewModelSortData *sort_data);

G_END_DECLS

#endif /* NAUTILUS_VIEW_MODEL_H */

