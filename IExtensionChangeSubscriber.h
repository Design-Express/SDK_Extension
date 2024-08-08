//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		enum class EUndoChangeType
		{
			Create = 0,
			Modify,
			Delete,
			Rename,
			MoveVector,
			MoveList,
			DeleteUndoPlaceholder,
			MoveUndoPlaceholder
		};

		enum class EChangeTypeFlags
		{
			CreateFlag = 1 << (Uint32) EUndoChangeType::Create,
			ModifyFlag = 1 << (Uint32) EUndoChangeType::Modify,
			DeleteFlag = 1 << (Uint32) EUndoChangeType::Delete,
			RenameFlag = 1 << (Uint32) EUndoChangeType::Rename,
			MoveVectorFlag = 1 << (Uint32) EUndoChangeType::MoveVector,
			MoveListFlag = 1 << (Uint32) EUndoChangeType::MoveList,
			DeleteUndoPlaceholderFlag = 1 << (Uint32) EUndoChangeType::DeleteUndoPlaceholder,
			MoveUndoPlaceholderFlag = 1 << (Uint32) EUndoChangeType::MoveUndoPlaceholder,

			// The flags that results in a list modification (i.e. prev, next, parent etc. is changed)
			ListModificationFlag =	(Uint32) EChangeTypeFlags::CreateFlag |
									(Uint32) EChangeTypeFlags::DeleteFlag |
									(Uint32) EChangeTypeFlags::MoveListFlag |
									(Uint32) EChangeTypeFlags::MoveUndoPlaceholderFlag |
									(Uint32) EChangeTypeFlags::DeleteUndoPlaceholderFlag,

			// All the flags
			AnyFlag =	(Uint32) EChangeTypeFlags::CreateFlag |
						(Uint32) EChangeTypeFlags::ModifyFlag |
						(Uint32) EChangeTypeFlags::DeleteFlag |
						(Uint32) EChangeTypeFlags::RenameFlag |
						(Uint32) EChangeTypeFlags::MoveVectorFlag |
						(Uint32) EChangeTypeFlags::MoveListFlag |
						(Uint32) EChangeTypeFlags::DeleteUndoPlaceholderFlag |
						(Uint32) EChangeTypeFlags::MoveUndoPlaceholderFlag
		};

		// Define bitwise operators for the flags enum, as they are used often.
		inline Uint32 operator | (EChangeTypeFlags lhs, EChangeTypeFlags rhs)
		{
			return static_cast<Uint32>(static_cast<Uint32>(lhs) | static_cast<Uint32>(rhs));
		}

		inline Uint32 operator & (EChangeTypeFlags lhs, EChangeTypeFlags rhs)
		{
			return static_cast<Uint32>(static_cast<Uint32>(lhs) & static_cast<Uint32>(rhs));
		}

		inline Uint32 operator & ( EChangeTypeFlags lhs, Uint32 rhs )
		{
			return static_cast<Uint32>(static_cast<Uint32>(lhs) & rhs);
		}

		inline Uint32 operator & ( Uint32 lhs, EChangeTypeFlags rhs )
		{
			return static_cast<Uint32>(lhs & static_cast<Uint32>(rhs));
		}

		inline Uint32 operator | ( EChangeTypeFlags lhs, Uint32 rhs )
		{
			return static_cast<Uint32>(static_cast<Uint32>(lhs) | rhs);
		}

		inline Uint32 operator | ( Uint32 lhs, EChangeTypeFlags rhs )
		{
			return static_cast<Uint32>(lhs | static_cast<Uint32>(rhs));
		}

		// ----------------------------------------------------------------------------------------------------
		class IChangeCollectionContext
		{
			public:
				class IChangeItem
				{
					public:
						virtual ~IChangeItem() {}

						virtual Uint32	GetChangeFlags() const = 0;
				};

			public:
				virtual		~IChangeCollectionContext() {}

				virtual bool IterateNonSuspendedObjects(std::function<bool (const MCObjectHandle&, const IChangeItem&)> callback) const = 0;
				virtual bool IterateAllObjects(std::function<bool (const MCObjectHandle&, const IChangeItem&)> callback) const = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		// {d4b0cd25-035c-4bfa-8f73-a93fb7a65644}
		static const VWGroupID GROUPID_ExtensionChangeSubscriber = { 0xd4b0cd25, 0x035c, 0x4bfa, { 0x8f, 0x73, 0xa9, 0x3f, 0xb7, 0xa6, 0x56, 0x44 } };

		// ----------------------------------------------------------------------------------------------------
		// Abstract class base for an change subscriber
		class DYNAMIC_ATTRIBUTE IExtensionChangeSubscriber : public IExtension
		{
			public:
				virtual void		VCOM_CALLTYPE	Notify(IChangeCollectionContext* context) = 0;
				virtual IEventSink* VCOM_CALLTYPE	QueryEventSink(const TSinkIID& iid) { return nullptr; }
		};

		typedef VCOMPtr<IExtensionChangeSubscriber>	IExtensionChangeSubscriberPtr;
	}
}
