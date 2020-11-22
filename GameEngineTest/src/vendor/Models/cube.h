#pragma once

namespace GameEngineTest 
{
	namespace Model
	{
		float lightSourceVertx[] =
		{
			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,

			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,

			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,

			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
		};

		float vertices[] = {
			//position						UV						Normals
		-0.5f, -0.5f, -0.5f,			 0.0f, 0.0f,			0.0f, 0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,			 1.0f, 0.0f,			0.0f, 0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,			 1.0f, 1.0f,			0.0f, 0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,			 1.0f, 1.0f,			0.0f, 0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,			 0.0f, 1.0f,			0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,			 0.0f, 0.0f,			0.0f, 0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,			 0.0f, 0.0f,			0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,			 1.0f, 0.0f,			0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,			 1.0f, 1.0f,			0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,			 1.0f, 1.0f,			0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,			 0.0f, 1.0f,			0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,			 0.0f, 0.0f,			0.0f, 0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,			 1.0f, 0.0f,		   -1.0f, 0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,			 1.0f, 1.0f,		   -1.0f, 0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,			 0.0f, 1.0f,		   -1.0f, 0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,			 0.0f, 1.0f,		   -1.0f, 0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,			 0.0f, 0.0f,		   -1.0f, 0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,			 1.0f, 0.0f,		   -1.0f, 0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,			 1.0f, 0.0f,			1.0f, 0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,			 1.0f, 1.0f,			1.0f, 0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,			 0.0f, 1.0f,			1.0f, 0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,			 0.0f, 1.0f,			1.0f, 0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,			 0.0f, 0.0f,			1.0f, 0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,			 1.0f, 0.0f,			1.0f, 0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,			 0.0f, 1.0f,			0.0f,-1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,			 1.0f, 1.0f,			0.0f,-1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,			 1.0f, 0.0f,			0.0f,-1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,			 1.0f, 0.0f,			0.0f,-1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,			 0.0f, 0.0f,			0.0f,-1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,			 0.0f, 1.0f,			0.0f,-1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,			 0.0f, 1.0f,			0.0f, 1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,			 1.0f, 1.0f,			0.0f, 1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,			 1.0f, 0.0f,			0.0f, 1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,			 1.0f, 0.0f,			0.0f, 1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,			 0.0f, 0.0f,			0.0f, 1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,			 0.0f, 1.0f,			0.0f, 1.0f,  0.0f
		};
	}
}