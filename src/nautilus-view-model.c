#include "nautilus-view-model.h"
#include "nautilus-view-item-model.h"
#include "nautilus-global-preferences.h"

struct _NautilusViewModel
{
  GObject parent_instance;

  GListStore *internal_model;
  NautilusViewModelSortData *sort_data;
};

G_DEFINE_TYPE (NautilusViewModel, nautilus_view_model, G_TYPE_OBJECT)

enum {
  PROP_0,
  PROP_SORT_TYPE,
  PROP_G_MODEL,
  N_PROPS
};

static void
finalize (GObject *object)
{
  G_OBJECT_CLASS (nautilus_view_model_parent_class)->finalize (object);
}

static void
get_property (GObject    *object,
              guint       prop_id,
              GValue     *value,
              GParamSpec *pspec)
{
  NautilusViewModel *self = NAUTILUS_VIEW_MODEL (object);

    switch (prop_id)
    {
        case PROP_SORT_TYPE:
        {
            g_value_set_object (value, self->sort_data);
        }
        break;

        case PROP_G_MODEL:
        {
            g_value_set_object (value, self->internal_model);
        }
        break;

        default:
        {
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        }
    }
}

static void
set_property (GObject      *object,
              guint         prop_id,
              const GValue *value,
              GParamSpec   *pspec)
{
  NautilusViewModel *self = NAUTILUS_VIEW_MODEL (object);

    switch (prop_id)
    {
        case PROP_SORT_TYPE:
        {
            nautilus_view_model_set_sort_type (self, g_value_get_object (value));
        }
        break;

        default:
        {
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        }
    }
}

static void
constructed (GObject *object)
{
    NautilusViewModel *self = NAUTILUS_VIEW_MODEL (object);

    G_OBJECT_CLASS (nautilus_view_model_parent_class)->constructed (object);

    self->internal_model = g_list_store_new (NAUTILUS_TYPE_VIEW_ITEM_MODEL);
}

static void
nautilus_view_model_class_init (NautilusViewModelClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize = finalize;
  object_class->get_property = get_property;
  object_class->set_property = set_property;
  object_class->constructed = constructed;
}

static void
nautilus_view_model_init (NautilusViewModel *self)
{
}

static gint
compare_data_func (gconstpointer a,
                   gconstpointer b,
                   gpointer      user_data)
{
    NautilusViewModel *self = NAUTILUS_VIEW_MODEL (user_data);
    NautilusFile *file_a;
    NautilusFile *file_b;

    file_a = nautilus_view_item_model_get_file (NAUTILUS_VIEW_ITEM_MODEL ((gpointer) a));
    file_b = nautilus_view_item_model_get_file (NAUTILUS_VIEW_ITEM_MODEL ((gpointer) b));

    return nautilus_file_compare_for_sort (file_a, file_b,
                                           self->sort_data->sort_type,
                                           self->sort_data->directories_first,
                                           self->sort_data->reversed);
}

NautilusViewModel *
nautilus_view_model_new ()
{
  return g_object_new (NAUTILUS_TYPE_VIEW_MODEL, NULL);
}

void
nautilus_view_model_set_sort_type (NautilusViewModel         *self,
                                   NautilusViewModelSortData *sort_data)
{
    if (self->sort_data)
    {
        g_free (self->sort_data);
    }

    self->sort_data = g_new (NautilusViewModelSortData, 1);
    self->sort_data->sort_type = sort_data->sort_type;
    self->sort_data->reversed = sort_data->reversed;
    self->sort_data->directories_first = sort_data->directories_first;

    g_list_store_sort (self->internal_model, compare_data_func, self);
}

GListStore *
nautilus_view_model_get_g_model (NautilusViewModel *self)
{
    return self->internal_model;
}
