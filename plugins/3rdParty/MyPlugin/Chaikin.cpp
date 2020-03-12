#include <ccPolyline.h>
#include <ccPointCloud.h>

static ccPolyline* SmoothChaikin(const ccPolyline& inputPolyline,
	PointCoordinateType ratio,
	unsigned iterations
	)
{
	if (iterations == 0)
	{
		assert(false);
		ccLog::Warning("SmoothChaikin: no iterations");
		return nullptr;
	}

	if (ratio < 0.05f || ratio > 0.45f)
	{
		assert(false);
		ccLog::Warning("SmoothChaikin: invalid ratio");
		return nullptr;
	}

	if (inputPolyline.size() > 2)
	{
		const ccPolyline* currentState = &inputPolyline;

		for (unsigned it = 0; it < iterations; ++it)
		{
			ccPointCloud* newStateVertices = new ccPointCloud("vertices");
			ccPolyline* newState = new ccPolyline(newStateVertices);
			newState->addChild(newStateVertices);

			if (!newStateVertices->reserve(currentState->size() * 2))
			{
				ccLog::Warning("SmoothChaikin: not enough memory");
				if (currentState != &inputPolyline)
				{
					delete currentState;
				}
				delete newState;
				return nullptr;
			}

			unsigned segmentCount = currentState->size();
			if (!inputPolyline.isClosed())
			{
				segmentCount--;
				//we always keep the first point
				newStateVertices->addPoint(*currentState->getPoint(0));
			}

			for (unsigned i = 0; i < segmentCount; ++i)
			{
				unsigned iP = i;
				unsigned iQ = ((iP + 1) % currentState->size());

				const CCVector3& P = *currentState->getPoint(iP);
				const CCVector3& Q = *currentState->getPoint(iQ);

				CCVector3 P0 = (PC_ONE - ratio) * P + ratio * Q;
				CCVector3 P1 = ratio * P + (PC_ONE - ratio) * Q;

				newStateVertices->addPoint(P0);
				newStateVertices->addPoint(P1);
			}

			if (!inputPolyline.isClosed())
			{
				//we always keep the last point
				newStateVertices->addPoint(*currentState->getPoint(currentState->size() - 1));
			}

			if (currentState != &inputPolyline)
			{
				delete currentState;
				currentState = nullptr;
			}

			if (!newState->reserve(newStateVertices->size()))
			{
				ccLog::Warning("SmoothChaikin: not enough memory");
				delete newState;
			}
			newState->addPointIndex(0, newStateVertices->size() - 1);

			if (it + 1 == iterations)
			{
				//last iteration (copy sate)
				newState->setClosed(inputPolyline.isClosed());
				newState->set2DMode(inputPolyline.is2DMode());
				newState->setGlobalShift(inputPolyline.getGlobalShift());
				newState->setGlobalScale(inputPolyline.getGlobalScale());
				newState->setVisible(inputPolyline.isVisible());
				newState->setEnabled(inputPolyline.isEnabled());
				newState->setName(inputPolyline.getName() + ".smoothed");

				return newState;
			}

			currentState = newState;
		}
	}
	else
	{
		ccLog::Warning("SmoothChaikin: not enough vertices");
	}

	return nullptr;
}
