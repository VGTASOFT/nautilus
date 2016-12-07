#ifndef NAUTILUS_VIEW_ICON_CONTROLLER_H
#define NAUTILUS_VIEW_ICON_CONTROLLER_H

#include <glib.h>
#include <gtk/gtk.h>

#include "nautilus-files-view.h"
#include "nautilus-window-slot.h"

G_BEGIN_DECLS

#define NAUTILUS_TYPE_VIEW_ICON_CONTROLLER (nautilus_view_icon_controller_get_type())

G_DECLARE_FINAL_TYPE (NautilusViewIconController, nautilus_view_icon_controller, NAUTILUS, VIEW_ICON_CONTROLLER, NautilusFilesView)

NautilusViewIconController *nautilus_view_icon_controller_new (NautilusWindowSlot *slot);

GListStore * nautilus_view_icon_controller_get_model (NautilusViewIconController *self);

G_END_DECLS

#endif /* NAUTILUS_VIEW_ICON_CONTROLLER_H */

