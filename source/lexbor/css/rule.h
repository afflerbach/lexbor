/*
 * Copyright (C) 2021-2022 Alexander Borisov
 *
 * Author: Alexander Borisov <borisov@lexbor.com>
 */

#ifndef LXB_CSS_RULE_H
#define LXB_CSS_RULE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lexbor/css/base.h"
#include "lexbor/css/at_rule.h"
#include "lexbor/css/property.h"
#include "lexbor/css/selectors/selectors.h"


#define lxb_css_rule(rule)                  ((lxb_css_rule_t *) (rule))
#define lxb_css_rule_list(rule)             ((lxb_css_rule_list_t *) (rule))
#define lxb_css_rule_at(rule)               ((lxb_css_rule_at_t *) (rule))
#define lxb_css_rule_style(rule)            ((lxb_css_rule_style_t *) (rule))
#define lxb_css_rule_bad_style(rule)        ((lxb_css_rule_bad_style_t *) (rule))
#define lxb_css_rule_declaration_list(rule) ((lxb_css_rule_declaration_list_t *) (rule))
#define lxb_css_rule_declaration(rule)      ((lxb_css_rule_declaration_t *) (rule))


typedef enum {
    LXB_CSS_RULE_UNDEF = 0,
    LXB_CSS_RULE_STYLESHEET,
    LXB_CSS_RULE_LIST,
    LXB_CSS_RULE_AT_RULE,
    LXB_CSS_RULE_STYLE,
    LXB_CSS_RULE_BAD_STYLE,
    LXB_CSS_RULE_DECLARATION_LIST,
    LXB_CSS_RULE_DECLARATION
}
lxb_css_rule_type_t;

typedef struct lxb_css_rule lxb_css_rule_t;

struct lxb_css_rule {
    lxb_css_rule_type_t type;
    lxb_css_rule_t      *next;
    lxb_css_rule_t      *prev;
    lxb_css_rule_t      *parent;

    const lxb_char_t    *begin;
    const lxb_char_t    *end;

    lxb_css_memory_t    *memory;
    size_t              ref_count;
};

struct lxb_css_rule_list {
    lxb_css_rule_t rule;

    lxb_css_rule_t *first;
    lxb_css_rule_t *last;
};

struct lxb_css_rule_at {
    lxb_css_rule_t rule;

    uintptr_t      type;

    union {
        lxb_css_at_rule__undef_t    *undef;
        lxb_css_at_rule__custom_t   *custom;
        lxb_css_at_rule_media_t     *media;
        lxb_css_at_rule_namespace_t *ns;
        void                        *user;
    } u;
};

struct lxb_css_rule_style {
    lxb_css_rule_t                  rule;

    lxb_css_selector_list_t         *selector;
    lxb_css_rule_declaration_list_t *declarations;
};

struct lxb_css_rule_bad_style {
    lxb_css_rule_t                  rule;

    lexbor_str_t                    selectors;
    lxb_css_rule_declaration_list_t *declarations;
};

struct lxb_css_rule_declaration_list {
    lxb_css_rule_t rule;

    lxb_css_rule_t *first;
    lxb_css_rule_t *last;

    size_t         count;
};

struct lxb_css_rule_declaration {
    lxb_css_rule_t rule;
    uintptr_t      type;

    union {
        lxb_css_property__undef_t         *undef;
        lxb_css_property__custom_t        *custom;
        lxb_css_property_display_t        *display;
        lxb_css_property_width_t          *width;
        lxb_css_property_height_t         *height;
        lxb_css_property_box_sizing_t     *box_sizing;
        lxb_css_property_margin_t         *margin;
        lxb_css_property_margin_top_t     *margin_top;
        lxb_css_property_margin_right_t   *margin_right;
        lxb_css_property_margin_bottom_t  *margin_bottom;
        lxb_css_property_margin_left_t    *margin_left;
        lxb_css_property_padding_t        *padding;
        lxb_css_property_padding_top_t    *padding_top;
        lxb_css_property_padding_right_t  *padding_right;
        lxb_css_property_padding_bottom_t *padding_bottom;
        lxb_css_property_padding_left_t   *padding_left;
        lxb_css_property_border_t         *border;
        lxb_css_property_border_top_t     *border_top;
        lxb_css_property_border_right_t   *border_right;
        lxb_css_property_border_bottom_t  *border_bottom;
        lxb_css_property_border_left_t    *border_left;
        void                              *user;
    } u;

    bool            important;
};


LXB_API void *
lxb_css_rule_destroy(lxb_css_rule_t *node, bool self_destroy);

LXB_API lxb_status_t
lxb_css_rule_serialize(const lxb_css_rule_t *rule,
                       lexbor_serialize_cb_f cb, void *ctx);

LXB_API lxb_status_t
lxb_css_rule_serialize_chain(const lxb_css_rule_t *rule,
                             lexbor_serialize_cb_f cb, void *ctx);

LXB_API lxb_css_rule_list_t *
lxb_css_rule_list_destroy(lxb_css_rule_list_t *list, bool self_destroy);

LXB_API lxb_status_t
lxb_css_rule_list_serialize(const lxb_css_rule_list_t *list,
                            lexbor_serialize_cb_f cb, void *ctx);

LXB_API lxb_css_rule_at_t *
lxb_css_rule_at_destroy(lxb_css_rule_at_t *at, bool self_destroy);

LXB_API lxb_status_t
lxb_css_rule_at_serialize(const lxb_css_rule_at_t *at, lexbor_serialize_cb_f cb,
                          void *ctx);

LXB_API lxb_status_t
lxb_css_rule_at_serialize_name(const lxb_css_rule_at_t *at, lexbor_serialize_cb_f cb,
                               void *ctx);

LXB_API lxb_css_rule_style_t *
lxb_css_rule_style_destroy(lxb_css_rule_style_t *style, bool self_destroy);

LXB_API lxb_status_t
lxb_css_rule_style_serialize(const lxb_css_rule_style_t *style,
                             lexbor_serialize_cb_f cb, void *ctx);

LXB_API lxb_css_rule_bad_style_t *
lxb_css_rule_bad_style_destroy(lxb_css_rule_bad_style_t *bad, bool self_destroy);

LXB_API lxb_status_t
lxb_css_rule_bad_style_serialize(const lxb_css_rule_bad_style_t *bad,
                                 lexbor_serialize_cb_f cb, void *ctx);

LXB_API lxb_css_rule_declaration_list_t *
lxb_css_rule_declaration_list_destroy(lxb_css_rule_declaration_list_t *list,
                                      bool self_destroy);

LXB_API lxb_status_t
lxb_css_rule_declaration_list_serialize(const lxb_css_rule_declaration_list_t *list,
                                        lexbor_serialize_cb_f cb, void *ctx);

LXB_API lxb_css_rule_declaration_t *
lxb_css_rule_declaration_destroy(lxb_css_rule_declaration_t *declr,
                                 bool self_destroy);

LXB_API lxb_status_t
lxb_css_rule_declaration_serialize(const lxb_css_rule_declaration_t *declaration,
                                   lexbor_serialize_cb_f cb, void *ctx);

LXB_API lxb_status_t
lxb_css_rule_declaration_serialize_name(const lxb_css_rule_declaration_t *declr,
                                        lexbor_serialize_cb_f cb, void *ctx);

/*
 * Inline functions
 */
lxb_inline void
lxb_css_rule_insert_next(lxb_css_rule_t *root, lxb_css_rule_t *rule)
{
    if (root->next != NULL) {
        rule->next = root->next;
    }

    root->next = rule;
    rule->prev = root;
}

lxb_inline lxb_css_rule_t *
lxb_css_rule_create(lxb_css_memory_t *memory, size_t size,
                    lxb_css_rule_type_t type)
{
    lxb_css_rule_t *rule;

    rule = (lxb_css_rule_t *) lexbor_mraw_calloc(memory->tree, size);
    if (rule== NULL) {
        return NULL;
    }

    rule->type = type;
    rule->memory = memory;

    return rule;
}

lxb_inline lxb_css_rule_list_t *
lxb_css_rule_list_create(lxb_css_memory_t *memory)
{
    return (lxb_css_rule_list_t *) lxb_css_rule_create(memory,
                                                       sizeof(lxb_css_rule_list_t),
                                                       LXB_CSS_RULE_LIST);
}

lxb_inline size_t
lxb_css_rule_ref_count(lxb_css_rule_t *rule)
{
    return rule->ref_count;
}

lxb_inline lxb_status_t
lxb_css_rule_ref_inc(lxb_css_rule_t *rule)
{
    if (SIZE_MAX - rule->ref_count == 0) {
        return LXB_STATUS_ERROR_OVERFLOW;
    }

    rule->ref_count++;

    return LXB_STATUS_OK;
}

lxb_inline void
lxb_css_rule_ref_dec(lxb_css_rule_t *rule)
{
    if (rule->ref_count > 0) {
        rule->ref_count--;
    }
}

lxb_inline void
lxb_css_rule_ref_dec_destroy(lxb_css_rule_t *rule)
{
    if (rule->ref_count > 0) {
        rule->ref_count--;
    }

    if (rule->ref_count == 0) {
        (void) lxb_css_rule_destroy(rule, true);
    }
}

lxb_inline void
lxb_css_rule_list_append(lxb_css_rule_list_t *list, lxb_css_rule_t *rule)
{
    if (list->first == NULL) {
        list->first = rule;
    }
    else {
        lxb_css_rule_insert_next(list->last, rule);
    }

    list->last = rule;
    rule->parent = lxb_css_rule(list);

    (void) lxb_css_rule_ref_inc(rule);
}

lxb_inline lxb_css_rule_at_t *
lxb_css_rule_at_create(lxb_css_memory_t *memory)
{
    return (lxb_css_rule_at_t *)
        lxb_css_rule_create(memory, sizeof(lxb_css_rule_at_t),
                            LXB_CSS_RULE_AT_RULE);
}

lxb_inline lxb_css_rule_style_t *
lxb_css_rule_style_create(lxb_css_memory_t *memory)
{
    return (lxb_css_rule_style_t *)
        lxb_css_rule_create(memory, sizeof(lxb_css_rule_style_t),
                            LXB_CSS_RULE_STYLE);
}

lxb_inline lxb_css_rule_bad_style_t *
lxb_css_rule_bad_style_create(lxb_css_memory_t *memory)
{
    return (lxb_css_rule_bad_style_t *)
        lxb_css_rule_create(memory, sizeof(lxb_css_rule_bad_style_t),
                            LXB_CSS_RULE_BAD_STYLE);
}

lxb_inline lxb_css_rule_declaration_list_t *
lxb_css_rule_declaration_list_create(lxb_css_memory_t *memory)
{
    return (lxb_css_rule_declaration_list_t *)
        lxb_css_rule_create(memory, sizeof(lxb_css_rule_declaration_list_t),
                            LXB_CSS_RULE_DECLARATION_LIST);
}

lxb_inline void
lxb_css_rule_declaration_list_append(lxb_css_rule_declaration_list_t *list,
                                     lxb_css_rule_t *rule)
{
    if (list->first == NULL) {
        list->first = rule;
    }
    else {
        lxb_css_rule_insert_next(list->last, rule);
    }

    list->last = rule;
    rule->parent = lxb_css_rule(list);

    (void) lxb_css_rule_ref_inc(rule);

    list->count++;
}

lxb_inline lxb_css_rule_declaration_t *
lxb_css_rule_declaration_create(lxb_css_memory_t *memory)
{
    return (lxb_css_rule_declaration_t *)
        lxb_css_rule_create(memory, sizeof(lxb_css_rule_declaration_t),
                            LXB_CSS_RULE_DECLARATION);
}


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LXB_CSS_RULE_H */
