#pragma once

namespace microservice
{
	struct server_version
	{
		static const char* GIT_SHA1;
		static const char* GIT_DATE;
		static const char* GIT_COMMIT_SUBJECT;
		static const char* GIT_BRANCH;
	};
}