// SPDX-License-Identifier: GPL-2.0
/*
 * Cirrus Logic CS35L41 MFD bd driver tests
 *
 * Copyright (C) 2020 Cirrus Logic, Inc. and
 *                    Cirrus Logic International Semiconductor Ltd.
 */

#include <kunit/test.h>
#include <kunit/mock.h>
#include <linux/device.h>
#include <linux/mfd/cs35l41/core.h>
#include <linux/mfd/cs35l41/registers.h>
#include <linux/mfd/cs35l41/calibration.h>
#include <linux/mfd/cs35l41/big_data.h>
#include <linux/mfd/cs35l41/power.h>
#include <linux/regmap.h>
#include <linux/typecheck.h>

/*
 * This is the most fundamental element of KUnit, the test case. A test case
 * makes a set EXPECTATIONs and ASSERTIONs about the behavior of some code; if
 * any expectations or assertions are not met, the test fails; otherwise, the
 * test passes.
 *
 * In KUnit, a test case is just a function with the signature
 * `void (*)(struct test *)`. `struct test` is a context object that stores
 * information about the current test.
 */

#if !defined(CONFIG_UML)
static void cs35l41_test_bd_suffix(struct test *test)
{
	test_info(test, "%s", __func__);
	return;
}

static void cs35l41_test_bd_store(struct test *test)
{
	const char *suffix_right = "_r";
	const char *suffix_wrong = "_x";

	test_info(test, "%s: start", __func__);
	cirrus_bd_store_values(suffix_right);
	cirrus_bd_store_values(suffix_wrong);
	test_info(test, "%s: end", __func__);
}

static void cs35l41_test_bd_add(struct test *test)
{
	const char *suffix_wrong = "_x";
	int ret;

	test_info(test, "%s: start", __func__);
	ret = cirrus_bd_amp_add(NULL, suffix_wrong, NULL, 0);
	EXPECT_EQ(test, ret, 0);
	test_info(test, "%s: end", __func__);
}
#endif

/*
 * This is run once before each test case, see the comment on
 * example_test_module for more information.
 */
static int cirrus_bd_test_init(struct test *test)
{
	return 0;
}

/*
 * This is run once after each test case, see the comment on example_test_module
 * for more information.
 */
static void cirrus_bd_test_exit(struct test *test)
{
}

/*
 * Here we make a list of all the test cases we want to add to the test module
 * below.
 */
static struct test_case cirrus_bd_test_cases[] = {
	/*
	 * This is a helper to create a test case object from a test case
	 * function; its exact function is not important to understand how to
	 * use KUnit, just know that this is how you associate test cases with a
	 * test module.
	 */
#if !defined(CONFIG_UML)
	TEST_CASE(cs35l41_test_bd_suffix),
	TEST_CASE(cs35l41_test_bd_store),
	TEST_CASE(cs35l41_test_bd_add),
#endif
	{},
};

/*
 * This defines a suite or grouping of tests.
 *
 * Test cases are defined as belonging to the suite by adding them to
 * `test_cases`.
 *
 * Often it is desirable to run some function which will set up things which
 * will be used by every test; this is accomplished with an `init` function
 * which runs before each test case is invoked. Similarly, an `exit` function
 * may be specified which runs after every test case and can be used to for
 * cleanup. For clarity, running tests in a test module would behave as follows:
 *
 * module.init(test);
 * module.test_case[0](test);
 * module.exit(test);
 * module.init(test);
 * module.test_case[1](test);
 * module.exit(test);
 * ...;
 */
static struct test_module cirrus_bd_test_module = {
	.name = "cirrus_bd_test",
	.init = cirrus_bd_test_init,
	.exit = cirrus_bd_test_exit,
	.test_cases = cirrus_bd_test_cases,
};

/*
 * This registers the above test module telling KUnit that this is a suite of
 * tests that need to be run.
 */
module_test(cirrus_bd_test_module);
