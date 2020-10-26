#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
template<class T> inline void WirteToBinStreamBase(std::ostream& os, const T& t);
template<class T> inline void WriteToBinStream(std::ostream& os, const T& t);
template<class T> inline void ReadFromBinStream(std::istream& is, T& t);
template<class T> inline T ReadFromBinStream(std::istream& is);
template<class T> inline void WirteToBinStreamBase(std::ostream& os, const typename std::vector<T>& vec);
template<class T> inline void ReadToBinStream(std::istream& is, const typename std::vector<T>& vec);

template<class T>
inline void WirteToBinStreamBase(std::ostream& os, const T& t)
{
	if (!os.write((const char*)&t), sizeof(T))
		return;
}

template<class T>
inline void WriteToBinStream(std::ostream& os, const T& t)
{
	WirteToBinStreamBase(os, t);
}

template<class T>
inline void ReadFromBinStream(std::istream& is, T& t)
{
	WirteToBinStreamBase(is, t);
}

template<class T>
inline T ReadFromBinStream(std::istream& is)
{
	T t;
	WirteToBinStreamBase(is, t);
	return t;
}

template<class T>
inline void WirteToBinStreamBase(std::ostream& os, const typename std::vector<T>& vec)
{
	WriteToBinStream<uint32_t>(os, vec.size());

	for (auto& iter : vec)
	{
		WriteToBinStream(os, iter);
	}
}

template<class T>
inline void ReadToBinStream(std::istream& is, const typename std::vector<T>& vec)
{
	vec.resize(ReadFromBinStream<uint32_t>(is));

	for (auto& iter : vec)
	{
		ReadFromBinStream(is, iter);
	}
}
