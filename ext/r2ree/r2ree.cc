#include "libr2ree.hh"
#include "string"
#include "iostream"
#include "ruby.h"

static VALUE rb_r2ree;

static VALUE r2ree_size(VALUE self); 
static VALUE r2ree_s_new(int argc, VALUE *argv, VALUE self); 
static VALUE r2ree_find(int argc, VALUE *argv, VALUE self); 
static VALUE r2ree_exist(int argc, VALUE *argv, VALUE self); 
static VALUE r2ree_size(VALUE self); 
static void r2ree_free(r2ree::radix_tree *tree); 

static void r2ree_free(r2ree::radix_tree *tree) {
  tree->~radix_tree();
  ruby_xfree(tree);
}

static VALUE r2ree_s_new(int argc, VALUE *argv, VALUE self) {
  int i = 0;
  VALUE paths, path;
  r2ree::radix_tree *tree = new r2ree::radix_tree();
  rb_scan_args(argc, argv, "1", &paths);

  if (TYPE(paths) == T_ARRAY) {
    while (!NIL_P(path = rb_ary_entry(paths, i))) {
      if (TYPE(path) != T_STRING)
        rb_raise(rb_eArgError, "wrong argument type, expected String");
      tree->insert(StringValuePtr(path));
      ++i;
    }
  }

  return Data_Wrap_Struct(self, NULL, r2ree_free, tree);
};

static VALUE r2ree_size(VALUE self) {
  int cid;
  r2ree::radix_tree *tree;
  Data_Get_Struct(self, r2ree::radix_tree, tree);
  cid = tree->cid;
  return INT2NUM(cid >= 0 ? cid + 1 : 0);
};

static VALUE r2ree_exist(int argc, VALUE *argv, VALUE self) {
  VALUE path;
  bool existence, leaf;
  r2ree::radix_tree *tree;
  r2ree::parse_result result;
  Data_Get_Struct(self, r2ree::radix_tree, tree);

  rb_scan_args(argc, argv, "1", &path);

  if (TYPE(path) == T_STRING) {
    result = tree->get(StringValuePtr(path));
    existence = std::get<0>(result);
    leaf = std::get<3>(result);
    return (existence && leaf) ? Qtrue : Qfalse;
  } else {
    return Qfalse;
  }
};

static VALUE r2ree_find(int argc, VALUE *argv, VALUE self) {
  int cid;
  bool existence, leaf;
  VALUE path;
  r2ree::radix_tree *tree;
  r2ree::parse_result result;
  Data_Get_Struct(self, r2ree::radix_tree, tree);

  rb_scan_args(argc, argv, "1", &path);

  if (TYPE(path) == T_STRING) {
    result = tree->get(StringValuePtr(path));
    existence = std::get<0>(result);
    cid = std::get<1>(result);
    leaf = std::get<3>(result);
    return (existence && leaf) ? INT2NUM(cid) : INT2NUM(-1);
  } else {
    rb_raise(rb_eArgError, "wrong argument type, expected String");
  }
};

extern "C" void Init_r2ree() {
  rb_r2ree = rb_define_class("R2ree", rb_cObject);

  rb_define_singleton_method(rb_r2ree, "new",        RUBY_METHOD_FUNC(r2ree_s_new), -1);
  rb_define_method(rb_r2ree,           "exist?",     RUBY_METHOD_FUNC(r2ree_exist), -1);
  rb_define_method(rb_r2ree,           "find",       RUBY_METHOD_FUNC(r2ree_find),  -1);
  rb_define_method(rb_r2ree,           "size",       RUBY_METHOD_FUNC(r2ree_size),   0);
  rb_define_alias(rb_r2ree, "length", "size");
};
