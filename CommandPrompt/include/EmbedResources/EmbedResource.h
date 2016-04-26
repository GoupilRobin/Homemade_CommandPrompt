#ifndef EmbedResource_h_
#define EmbedResource_h_

namespace embed_res
{
	class EmbedResource
	{
	public:
		virtual char * GetData() const = 0;
		virtual unsigned long GetSize() const = 0;
	};
}

#endif