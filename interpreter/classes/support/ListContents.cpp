/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Copyright (c) 1995, 2004 IBM Corporation. All rights reserved.             */
/* Copyright (c) 2005-2014 Rexx Language Association. All rights reserved.    */
/*                                                                            */
/* This program and the accompanying materials are made available under       */
/* the terms of the Common Public License v1.0 which accompanies this         */
/* distribution. A copy is also available at the following address:           */
/* http://www.oorexx.org/license.html                                         */
/*                                                                            */
/* Redistribution and use in source and binary forms, with or                 */
/* without modification, are permitted provided that the following            */
/* conditions are met:                                                        */
/*                                                                            */
/* Redistributions of source code must retain the above copyright             */
/* notice, this list of conditions and the following disclaimer.              */
/* Redistributions in binary form must reproduce the above copyright          */
/* notice, this list of conditions and the following disclaimer in            */
/* the documentation and/or other materials provided with the distribution.   */
/*                                                                            */
/* Neither the name of Rexx Language Association nor the names                */
/* of its contributors may be used to endorse or promote products             */
/* derived from this software without specific prior written permission.      */
/*                                                                            */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS        */
/* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT          */
/* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS          */
/* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT   */
/* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,      */
/* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED   */
/* TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,        */
/* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY     */
/* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING    */
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS         */
/* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/******************************************************************************/
/* REXX Kernel                                                                */
/*                                                                            */
/* Code for the table backing the List class                                  */
/*                                                                            */
/******************************************************************************/
#include "RexxCore.h"
#include "ListClass.hpp"
#include "Memory.hpp"


/**
 * Allocate memory for a new ListContents entry.
 *
 * @param size   The base object size.
 * @param initialSize
 *               The initial number of entries
 *
 * @return The storage for a new table object.
 */
void *ListContents::operator new(size_t size, size_t initialSize)
{
    return new_object(size + sizeof(ListEntry) * (initialSize - 1), T_ListContents);
}


/**
 * Construct a ListContent item of the given size.
 *
 * @param size   The total number of entries in the object.
 */
ListContents::ListContents(size_t size)
{
    // clear the entire object for safety
    clearObject();

    // this is the total size of the bucket
    totalSize = size;

    // no first or last items.
    firstItem = NoMore;
    lastItem = NoMore

    // initialize the free chains
    initializeFreeChain();
}


/**
 * Initialize the free chains, either at construction time or
 * after an empty() operation.
 */
void ListContents::initializeFreeChain()
{
    // this is an empty bucket
    itemCount = 0;

    // we keep the available items on a chain, so
    // chain up the items into a free chain
    freeChain = 0;

    for (ItemLink i = freeChain; i < totalSize; i++)
    {
        entries[i].next = i + 1;
    }
    // make sure the last item ends the chain.  Note, we
    // don't bother double linking the free chain since we
    // only remove from the front.
    entries[totalSize - 1].next = NoMore;
}


/**
 * Normal garbage collection live marking
 *
 * @param liveMark The current live mark.
 */
void ListContents::live(size_t liveMark)
{
    // we only mark the active items rather than scanning the entire content area.
    for (size_t position = firstItem; position != NoMore; position = nextEntry(position))
    {
        memory_mark(entries[position].value);
    }
}


/**
 * Generalized object marking.
 *
 * @param reason The reason for this live marking operation.
 */
void ListContents::liveGeneral(MarkReason reason)
{
    // we only mark the active items rather than scanning the entire content area.
    for (size_t position = firstItem; position != NoMore; position = nextEntry(position))
    {
        memory_mark_general(entries[position].value);
    }
}


/**
 * Flatten the table contents as part of a saved program.
 *
 * @param envelope The envelope we're flattening into.
 */
void ListContents::flatten(RexxEnvelope *envelope)
{
    setUpFlatten(ListContents)

    // we only mark the active items rather than scanning the entire content area.
    for (size_t position = firstItem; position != NoMore; position = nextEntry(position))
    {
        memory_mark_general(entries[position].value);
    }

    cleanUpFlatten
}


/**
 * Merge the list maintained in this contents object into
 * a target one after an expansion has occurred.
 *
 * @param target The target contents.
 */
void ListContents::mergeInto(ListContents *target)
{
    // NOTE:  This assumes the target contents item is at least
    // as large as this one.

    // run the chain appending each item on to the target
    for (size_t position = firstItem; position != NoMore; position = nextEntry(position))
    {
        target->append(entryValue(i));
    }
}


/**
 * Allocate a slot for a new value and fill it in.
 *
 * @param value  The value we're inserting.
 *
 * @return The index position for the inserted item.
 */
ItemLink ListContents::allocateSlot(RexxInternalOBject *value)
{
    // this is a nice central place to handle bumping the count
    itemCount++;

    // get an item off of the chain and set the value
    ItemLink newItem = freeChain;
    freeChain = nextEntry(newItem);

    setEntryValue(newItem, value);
    return newItem;
}


/**
 * Insert an item at the end of the existing list.
 *
 * @param newItem The new item we're inserting.
 */
void ListContents::insertAtEnd(ItemLink newItem)
{
    // first insertion into this list?
    if (lastItem = NoMore)
    {
        // make this the first and last, and leave all of its links
        // as terminators
        firstItem = newItem;
        lastItem = newItem;
    }
    // insert after this item
    else
    {
        insertAfter(newItem, lastItem);
    }
}


/**
 * Insert an item at the front of the existing list.
 *
 * @param newItem The new item we're inserting.
 */
void ListContents::insertAtFront(ItemLink newItem)
{
    // first insertion into this list?
    if (firstItem = NoMore)
    {
        // make this the first and last, and leave all of its links
        // as terminators
        firstItem = newItem;
        lastItem = newItem;
    }
    // insert before the first item
    else
    {
        insertAfter(newItem, firstItem);
    }
}


/**
 * Insert an item after a given list item.
 *
 * @param newItem    The new item we're inserting.
 * @param insertItem The item this is inserted after.
 */
void ListContents::insertAfter(ItemLink newItem, ItemLink insertItem)
{
    // the new item gets the next item of our predecessor
    setNext(newItem, nextEntry(insertItem));
    // set the next and previous of these two to point at each other
    setNext(insertItem, newItem);
    setPrevious(newItem, insertItem);

    // do we have a following item?...if not, we're the new last item
    if (nextEntry(newItem) == NoMore)
    {
        lastItem = newItem
    }
    // need to update the item after us to point back to us
    else
    {
        setPrevious(nextEntry(newItem), newItem)
    }
}


/**
 * Insert an item before a given list item.
 *
 * @param newItem    The new item we're inserting.
 * @param insertItem The item this is inserted before.
 */
void ListContents::insertBefore(ItemLink newItem, ItemLink insertItem)
{
    // the new item gets the prevous item of our predecessor
    setPrevious(newItem, previousEntry(insertItem));
    // set the next and previous of these two to point at each other
    setPrevious(insertItem, newItem);
    setNext(newItem, insertItem);

    // do we have a previous item?...if not, we're the new first item
    if (previousEntry(insertItem) == NoMore)
    {
        firstItem = newItem
    }
    // need to update the item after us to point back to us
    else
    {
        setNext(previousEntry(newItem), newItem)
    }
}


/**
 * Add a value to the list at a given index position.
 *
 * @param value  The value to add.
 * @param index  The target index postion.  NoMore indicates add to the end.
 *
 * @return The index position of the new item.
 */
ItemLink ListContents::insert(RexxInternalObject *value, ItemLink index)
{
    newItem = allocateSlot(value);
    // if we got a .nil index for the insertion, this is at the beginning.
    if (index == AtEnd)
    {
        insertAtEnd(newItem);
    }
    if (index == AtBeginning)
    {
        insertAtFront(newItem);
    }
    else
    {
        // this is inserted before the index position
        insertBefore(newItem, index);
    }

    // return the new index
    return newItem;
}


/**
 * Add a value to the beginning of the list
 *
 * @param value  The value to add.
 *
 * @return The index position of the new item.
 */
ItemLink ListContents::insertAtBeginning(RexxInternalObject *value)
{
    newItem = allocateSlot(value);
    insertAtFront(newItem);
    // return the new index
    return newItem;
}


/**
 * Add a value to the beginning of the list
 *
 * @param value  The value to add.
 *
 * @return The index position of the new item.
 */
ItemLink ListContents::insertAtEnd(RexxInternalObject *value)
{
    newItem = allocateSlot(value);
    insertAtEnd(newItem);
    // return the new index
    return newItem;
}


/**
 * Remove an item postion from the chain and return
 * the location to the free chain.
 *
 * @param item   The item position to remove.
 */
void ListContents::removeItem(ItemLink item)
{
    // we have one fewer item now.
    itemCount--;

    // handle being just the only item first, since it
    // simplifies some things by removing that possibility first
    if (item == firstItem)
    {
        // first and last, this is easy.
        if (item == lastItem)
        {
            firstItem = NoMore;
            lastItem = NoMore;
        }
        // removing the first item, promote our
        // successor to the front
        else
        {
            firstItem = nextEntry(item);
            setPrevious(firstItem, NoMore);
        }

    }
    // not the first, could be the last
    else if (item == lastItem)
    {
        lastItem = previousEntry(item);
        setNext(lastItem, NoMore);
    }
    // have both a previous and next,
    else
    {
        // update the next item first
        setPrevious(nextEntry(item), previousEntry(item))
        // and the reverse for our previous item
        setNext(previousEntry(item), nextEntry(item))
    }

    // put this back on the free chain
    returnToFreeChain(item);
}


/**
 * Retrieve an index from the contents.
 *
 * @param index  The index position.
 *
 * @return The associated value.
 */
RexxInternalObject *ListContents::get(ItemLink index)
{
    return isIndexValid(index) ? OREF_NULL : entryValue(index);
}


/**
 * Perform a PUT() operation on an existing index, replacing
 * the existing value.
 *
 * @param value  The new value
 * @param index  The index position.
 *
 * @return The old value or OREF_NULL if this is not a valid index.
 */
RexxInternalObject *ListContents::put(RexxInternalObject value, ItemLink index)
{
    if (!isIndexValid(index))
    {
        return OREF_NULL;
    }

    RexxInternalObject *oldValue = entryValue(index);
    setValue(index, value);
    return oldValue;
}


/**
 * Remove an item from the list at a given index.
 *
 * @param index  The target index.
 *
 * @return The removed item, if any.
 */
RexxInternalObject *ListContents::remove(ItemLink index)
{
    // this might have been out of bounds or obsolete...just return
    // NULL because there's nothing to remove.
    if (index == NoLink)
    {
        return OREF_NULL;
    }

    // get the current item before removing this from the chain.  That
    // is our return value.
    RexxInternalObject *removed = entryValue(index);
    removeItem(index);
}


/**
 * Return the first item in the list.
 *
 * @return The first item, or OREF_NULL if the list is empty.
 */
RexxInternalObject *ListContents::firstItem()
{
    if (firstItem == NoMore)
    {
        return OREF_NULL;
    }

    return entryValue(firstItem);
}


/**
 * Return the last item in the list.
 *
 * @return The last item, or OREF_NULL if the list is empty.
 */
RexxInternalObject *ListContents::lastItem()
{
    if (lastItem == NoMore)
    {
        return OREF_NULL;
    }

    return entryValue(lastItem);
}


/**
 * Return the index of the first item in the list.
 *
 * @return The first item index, or NoMore
 */
ItemLink ListContents::firstIndex()
{
    return firstItem;
}


/**
 * Return the index of the last item in the list.
 *
 * @return The last item index, or NoMore if the list is empty
 */
ItemLink ListContents::lastIndex()
{
    return lastIndex;
}


/**
 * Get the index of the next item after a target item.
 *
 * @param item   The item index.
 *
 * @return The next item.  NoMore indicates there is no next item.
 */
ItemLink ListContents::nextIndex(ItemLink item)
{
    return item == NoMore ? NoMore : nextEntry(item);
}


/**
 * Get the index of the item before a given index.
 *
 * @param item   The target item.
 *
 * @return The item index, or NoMore if there is not valid previous item.
 */
ItemLink ListContents::previousIndex(ItemLink item)
{
    return item == NoMore ? NoMore : previousEntry(item);
}


/**
 * Get all of the items in the list as an array item.
 *
 * @return An array containing all of the items.
 */
RexxArray *ListContents::allItems()
{
    RexxArray *items = new_array(items());

    for (size_t position = firstItem; position != NoMore; position = nextEntry(position))
    {
        items->append(entryValue(position));
    }

    return items
}


/**
 * Get all of the indexes in the list as an array item.
 *
 * @return An array containing all of the indexes.
 */
RexxArray *ListContents::allIndexes()
{
    RexxArray *items = new_array(items());

    for (size_t position = firstItem; position != NoMore; position = nextEntry(position))
    {
        items->append(new_integer(position)));
    }

    return items
}


/**
 * Empty the list of all contents.
 */
void ListContents::empty()
{
    // clear all of the entries so we handle old-to-new properly.
    for (size_t position = firstItem; position != NoMore;)
    {
        // get the next link before clearing
        ItemLink next = nextEntry(position);
        clearEntry(position);
        position = next;
    }

    // reset the free chains
    initializeFreeChain();
}


/**
 * Find the index for a target item.
 *
 * @param target The target item.
 *
 * @return The index of the located item or NoMore if this cannot be found.
 */
ItemLink ListContents::getIndex(RexxInternalObject *target)
{
    // scan until we get a hit.
    for (size_t position = firstItem; position != NoMore; position = nextEntry(position))
    {
        if (target->equalValue(entryValue(position)))
        {
            return position;
        }
    }
    return NoMore;
}


/**
 * Remove an item from the collection.
 *
 * @param target The target item.
 *
 * @return The actual stored object value.
 */
RexxInternalObject *ListContents::removeItem(RexxInternalObject *target)
{
    // scan for the item until we get a hit.  Return the object that is actually there.
    for (size_t position = firstItem; position != NoMore; position = nextEntry(position))
    {
        if (target->equalValue(entryValue(position)))
        {
            RexxInternalObject *removed = entryValue(position);
            removeItem(position);
            return removed;
        }
    }
    return OREF_NULL;
}


/**
 * Create a supplier for the collection.
 *
 * @return A supplier for iterating over the collection.
 */
SupplierClass *ListContents::supplier()
{
    RexxArray *indexes = allIndexes();
    RexxArray *values = allItems();
    return new_supplier(values, indices);
}


/**
 * Not really part of normal list operation, but classes
 * maintain their subclasses as a list of weak references
 * so that subclasses can get garbage collected when no
 * longer needed.  When the class needs to iterate over
 * the subclasses, it needs to resolve which weak references
 * are still valid.  This method will check the weak
 * references and remove any stale entries.  Then it
 * will return an array of the dereferenced objects.
 *
 * @return An array of the dereferenced objects.
 */
RexxArray *ListContents::weakReferenceArray()
{
    // this is a little tricky.  We allocate the result array
    // before we process the weak references.  If we prune
    // the stale references first and then allocate an array,
    // we might hit a GC window that could create more stale
    // references.

    // make this larg enough to hold what is currently there.
    // this could be more than we need, but that's fine.
    // TODO:  make sure subclasses uses items() rather than size()
    Protected<RexxArray> result = new_array(items());

    size_t position = firstItem;
    while (position != NoMore)
    {
        // get the next position before processing the current link
        ItemLink next = nextEntry(position);

        // get the reference value and see if it is still valid
        // if not, just delink this position and allow the weak reference
        // to be garbage collected.
        WeakReference *ref = (WeakReference *)entryValue(position);
        if (!ref->hasReferent())
        {
            removeItem(position);
        }
        // we have a good value, so add this to the result array.
        else
        {
            result->append(ref->get());
        }
        // now step to the next position
        position = next;
    }
    return result;
}
