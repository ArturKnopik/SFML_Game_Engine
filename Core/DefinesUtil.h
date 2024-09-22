#pragma once

#define UNUSED(x) (void)(x)

#define GOTO_END_ON_ERROR(err) \
	if ((err) != kod::Error::OK) { \
		goto end; \
	}