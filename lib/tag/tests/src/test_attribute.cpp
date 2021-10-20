#include "gtest/gtest.h"

#include <cstring>

extern "C"
{
#include "attribute.h"
}

TEST(init_attribute, init_attribute) {
  attribute_t attribute = {};
  init_attribute(&attribute);
  EXPECT_EQ(attribute.name, (void*)NULL);
  EXPECT_EQ(attribute.value, (void*)NULL);
}

TEST(init_attribute, init_attribute_null) {
  attribute_t* attribute = NULL;
  init_attribute(attribute);
}

TEST(create_free_attribute, create_free_attribute) {
  attribute_t* attribute = create_attribute();
  EXPECT_NE(attribute, (void*)NULL);
  attribute = free_attribute(attribute);
  EXPECT_EQ(attribute, (void*)NULL);
}

TEST(set_attribute_name, set_attribute_name) {
  attribute_t attribute = {};
  const char* name = "name";
  tag_error_t result = set_attribute_name(&attribute, name);
  EXPECT_EQ(result, ERROR_OK);
  EXPECT_NE(attribute.name, name);
  EXPECT_EQ(strcmp(name, attribute.name), 0);
  clear_attribute(&attribute);
}

TEST(set_attribute_name, set_attribute_name_null) {
  attribute_t* attribute = NULL;
  tag_error_t result = set_attribute_name(attribute, "name");
  EXPECT_EQ(result, ERROR_NULL_PTR_REFERENCE);
}

TEST(set_attribute_name, set_attribute_name_empty) {
  attribute_t attribute = {};
  const char* name = "";
  tag_error_t result = set_attribute_name(&attribute, name);
  EXPECT_EQ(result, ERROR_OK);
  EXPECT_NE(attribute.name, name);
  EXPECT_EQ(strcmp(name, attribute.name), 0);
  clear_attribute(&attribute);
}

TEST(set_attribute_value, set_attribute_value) {
  attribute_t attribute = {};
  const char* value = "value";
  tag_error_t result = set_attribute_value(&attribute, value);
  EXPECT_EQ(result, ERROR_OK);
  EXPECT_NE(attribute.value, value);
  EXPECT_EQ(strcmp(value, attribute.value), 0);
  clear_attribute(&attribute);
}

TEST(set_attribute_value, set_attribute_value_empty) {
  attribute_t attribute = {};
  const char* value = "";
  tag_error_t result = set_attribute_value(&attribute, value);
  EXPECT_EQ(result, ERROR_OK);
  EXPECT_NE(attribute.value, value);
  EXPECT_EQ(strcmp(value, attribute.value), 0);
  clear_attribute(&attribute);
}

TEST(set_attribute_value, set_attribute_value_null) {
  attribute_t* attribute = NULL;
  tag_error_t result = set_attribute_value(attribute, "value");
  EXPECT_EQ(result, ERROR_NULL_PTR_REFERENCE);
}

TEST(clear_attribute, clear_attribute_empty) {
  attribute_t attribute = {};
  clear_attribute(&attribute);

  EXPECT_EQ(attribute.name, (void*)NULL);
  EXPECT_EQ(attribute.value, (void*)NULL);
}

TEST(clear_attribute, clear_attribute) {
  attribute_t attribute = {};
  set_attribute_name(&attribute, "name");
  set_attribute_value(&attribute, "value");

  clear_attribute(&attribute);
  EXPECT_EQ(attribute.name, (void*)NULL);
  EXPECT_EQ(attribute.value, (void*)NULL);
}

TEST(clear_attribute, clear_attribute_null) {
  attribute_t* attribute = NULL;
  clear_attribute(attribute);
}

