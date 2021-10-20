#include "gtest/gtest.h"


extern "C"
{
#include "tag.h"
#include "string.h"
}

TEST(init_tag, init_tag) {
  tag_t tag = {};
  init_tag(&tag);
  EXPECT_EQ(tag.name, (void*)NULL);
  EXPECT_EQ(tag.is_closed, false);
  EXPECT_EQ(tag.attributes, (void*)NULL);
  EXPECT_EQ(tag.attributes_count, 0);
}

TEST(init_tag, init_tag_null) {
  tag_t* tag = NULL;
  init_tag(tag);
}

TEST(create_free_tag, create_free_tag) {
  tag_t* tag = create_tag();
  EXPECT_NE(tag, (void*)NULL);
  tag = free_tag(tag);
  EXPECT_EQ(tag, (void*)NULL);
}

TEST(add_tag_attribute, add_tag_attribute) {
  tag_t tag = {};
  attribute_t attribute = {};
  set_attribute_name(&attribute, "name");
  set_attribute_value(&attribute, "value");

  tag_error_t result = add_tag_attribute(&tag, &attribute);
  EXPECT_EQ(result, ERROR_OK);
  EXPECT_EQ(tag.attributes_count, 1);
  EXPECT_EQ(strcmp(tag.attributes[0].name, "name"), 0);
  EXPECT_EQ(strcmp(tag.attributes[0].value, "value"), 0);
  clear_tag(&tag);
  clear_attribute(&attribute);
}

TEST(add_tag_attribute, add_tag_attribute_null_tag) {
  tag_t* tag = NULL;
  attribute_t attribute = {};
  set_attribute_name(&attribute, "name");
  set_attribute_value(&attribute, "value");

  tag_error_t result = add_tag_attribute(tag, &attribute);
  EXPECT_EQ(result, ERROR_NULL_PTR_REFERENCE);
  clear_attribute(&attribute);
}

TEST(add_tag_attribute, add_tag_attribute_null_attribute) {
  tag_t tag = {};
  attribute_t* attribute = NULL;
  tag_error_t result = add_tag_attribute(&tag, attribute);
  EXPECT_EQ(result, ERROR_NULL_PTR_REFERENCE);
}

TEST(set_tag_name, set_tag_name) {
  tag_t tag = {};
  tag_error_t result = set_tag_name(&tag, "name");
  EXPECT_EQ(strcmp(tag.name, "name"), 0);
  clear_tag(&tag);
}

