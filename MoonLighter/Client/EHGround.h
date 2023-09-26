#pragma once

#include "EHScript.h"

namespace EH
{
	class Ground : public Script
	{
	public:
		Ground();
		virtual ~Ground();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	private:

	};
}


