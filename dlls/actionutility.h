#ifndef ACTION_UTILITY_H
#define ACTION_UTILITY_H

#include <vector>

//using namespace std;

class CActionUtility
{
public:
	CActionUtility(eCanDoStuff action, bool utility)
	{
		m_Action = action;
		m_fUtility = utility;
	}

	float getUtility() const
	{
		return m_fUtility;
	}

	eCanDoStuff getAction() const
	{
		return m_Action;
	}

private:
	eCanDoStuff m_Action;
	bool m_fUtility;
};

class CActionUtilities
{
public:
	void add(eCanDoStuff action, BOOL CanDo, float utility)
	{
		//m_Utilities.emplace_back(CActionUtility(action, (float)CanDo * utility));
		m_Utilities.emplace_back(action, static_cast<float>(CanDo) * utility);
	}

	eCanDoStuff getBestAction() const
	{
		const float rand = RANDOM_FLOAT(0, getTotalUtility());

		float total = 0.0f;

		for (auto m_Utility : m_Utilities)
		{
			total += m_Utility.getUtility();

			if (m_Utility.getUtility() && rand < total)
				return m_Utility.getAction();
		}

		return BOT_CAN_NONE;
	}

	float getTotalUtility() const
	{
		float total = 0.0f;

		for (auto m_Utility : m_Utilities)
		{
			total += m_Utility.getUtility();
		}

		return total;
	}
private:
	std::vector<CActionUtility> m_Utilities;
};

#endif