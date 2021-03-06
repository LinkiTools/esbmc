#include <langapi/mode.h>
#include <esbmc/version.h>

const mode_table_et mode_table[] =
{
  LANGAPI_HAVE_MODE_C,
#ifndef WITHOUT_CLANG
  LANGAPI_HAVE_MODE_CLANG_C,
#endif
  LANGAPI_HAVE_MODE_CPP,
#ifndef WITHOUT_CLANG
  LANGAPI_HAVE_MODE_CLANG_CPP,
#endif
  LANGAPI_HAVE_MODE_END
};

extern "C" uint8_t buildidstring_buf[1];
uint8_t *esbmc_version_string = buildidstring_buf;

extern "C" {
uint64_t esbmc_version = ESBMC_VERSION_CONST;
}
